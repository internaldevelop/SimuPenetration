#include "controlcmd.h"

#include "c37292.h"

controlcmd::controlcmd(QWidget *parent) : QWidget(parent)
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

    connect(m_buttonStopPLC, SIGNAL(clicked()), this, SLOT(stopPLC()));
    connect(m_buttonStartPLC, SIGNAL(clicked()), this, SLOT(startPLC()));

    this->setAutoFillBackground(true);
}


void controlcmd::initWidget()
{
    m_widget = new QWidget();
    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(680,320);

    m_inputIp = new QLineEdit();
    m_inputIp->setText("192.168.1.50");
    m_inputIp->setFixedSize(100, 24);

    m_inputPort = new QLineEdit();
    m_inputPort->setText("44818");
    m_inputPort->setFixedSize(100, 24);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonStopPLC= new QPushButton();
    m_buttonStopPLC->setText(tr("关停PLC"));
    m_buttonStopPLC->setFont(fontButton);

    m_buttonStartPLC= new QPushButton();
    m_buttonStartPLC->setText(tr("开启PLC"));
    m_buttonStartPLC->setFont(fontButton);

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
    widget_2_H_layout->addWidget(m_buttonStopPLC);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonStartPLC);//, 0, Qt::AlignLeft);
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
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widget->setLayout(main_layout);
}

void controlcmd::stopPLC()
{

}

void controlcmd::startPLC()
{

}
