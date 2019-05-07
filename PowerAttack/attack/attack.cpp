#include "attack.h"

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
    this->setAutoFillBackground(true);

}


void attack::initWidget()
{
    m_widget = new QWidget();
    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(680,320);

    m_inputIp = new QLineEdit();
    m_inputIp->setText("127.0.0.1");
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
        m_buttonICMP->setEnabled(true);
        m_buttonLAND->setEnabled(true);
        m_buttonSYN->setText("SYN Flood攻击");

        psyn->set_sig_int();

        appendOutput("攻击已停止");

    }
    else {
        m_buttonICMP->setEnabled(false);
        m_buttonLAND->setEnabled(false);

        appendOutput("开始攻击");

        QByteArray ba = m_inputIp->text().toLatin1();
        psyn->do_main(ba.data(),m_inputPort->text().toInt());

        m_buttonSYN->setText("停止攻击");

    }


}
void attack::icmp_flood()
{
    if(m_buttonICMP->text()=="停止攻击")
    {
        m_buttonSYN->setEnabled(true);
        m_buttonLAND->setEnabled(true);
        m_buttonICMP->setText("ICMP Flood攻击");

        picmp->set_sig_int();
        appendOutput("攻击已停止");

    }
    else {
        appendOutput("开始攻击");

        m_buttonSYN->setEnabled(false);
        m_buttonLAND->setEnabled(false);


        QByteArray ba = m_inputIp->text().toLatin1();

        picmp->do_main(ba.data());
        m_buttonICMP->setText("停止攻击");

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

        m_buttonSYN->setEnabled(false);
        m_buttonICMP->setEnabled(false);


        QByteArray ba = m_inputIp->text().toLatin1();
//        psyn->do_main(ba.data(),m_inputPort->text().toInt());
        m_buttonLAND->setText("停止攻击");

    }

}

void attack::appendOutput(QString output) {
    QString strOldRecord = m_textResult->placeholderText().left(1024);
    m_textResult->setPlaceholderText(strOldRecord + "\n" + output);
}

