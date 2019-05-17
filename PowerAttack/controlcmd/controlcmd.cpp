#include "controlcmd.h"

#include "c37292.h"

extern QString getcurrenttime();

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
    m_textResult = new QTextEdit();
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


    m_buttonStartPLC= new QPushButton();
    QPixmap pixmap(":/sys_test_widget/start");
    m_buttonStartPLC->setIcon(pixmap);
//    m_buttonStartPLC->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
//    m_buttonStartPLC->setStyleSheet("QPushButton{background-color:black;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}" //按键本色
//                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
//                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
//                                   );
    m_buttonStartPLC->setStyleSheet(
                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
                                   );

    m_buttonStartPLC->setIconSize(pixmap.size());
    m_buttonStartPLC->setFixedSize(180, 70);
    m_buttonStartPLC->setObjectName("redButton");

    m_buttonStartPLC->setText(tr("开启PLC"));
    m_buttonStartPLC->setFont(fontButton);


    m_buttonStopPLC= new QPushButton();
    QPixmap pixmapstop(":/sys_test_widget/stop");
    m_buttonStopPLC->setIcon(pixmapstop);
//    m_buttonStopPLC->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    m_buttonStopPLC->setStyleSheet(
                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
                                   );

    m_buttonStopPLC->setIconSize(pixmapstop.size());
    m_buttonStopPLC->setFixedSize(180, 70);
    m_buttonStopPLC->setObjectName("greenButton");

    m_buttonStopPLC->setText(tr("关停PLC"));
    m_buttonStopPLC->setFont(fontButton);

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
    widget_2_H_layout->addWidget(m_buttonStartPLC);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonStopPLC);//, 0, Qt::AlignLeft);
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
    appendOutput("正在进行PLC通讯，发送关闭指令：");
    appendOutput("776d736762000021000025000010000c000000000000000100000000776d736765");
    appendOutput("PLC关闭成功.");

}

void controlcmd::startPLC()
{
    appendOutput("正在进行PLC通讯，发送开启指令：");
    appendOutput("776d736762000021000025000010000c000000000000000000000000776d736765");
    appendOutput("PLC 开启指令成功.");

}

void controlcmd::appendOutput(QString output)
{
//    QString strOldRecord = m_textResult->placeholderText().left(1024);
//    m_textResult->setPlainText(strOldRecord + "\n" + output);
    output = "["+getcurrenttime()+"] "+output+"\n";

    QString strOldRecord = m_textResult->toPlainText().left(1024);
    m_textResult->setPlainText(strOldRecord + output);

}
