#include "systemdata.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPrinter>
#include <QProcess>
#include <qdebug.h>
#include <QPainter>
#include <QFile>
#include <QPdfWriter>
#include <QDateTime>

#include <Utils/csysutils.h>
#include <Utils/cwebutils.h>
#include "c37292.h"

systemdata::systemdata(QWidget *parent) : QWidget(parent)
{
    // 初始化左侧功能列表
    initItemList();

    // 初始化页面
    initPasswordWidget();
    // 初始化页面
    initSysConfigWidget();

    // 将功能页面存放到堆栈里
    m_stackWidget = new QStackedWidget();
    m_stackWidget->addWidget(m_widgetPassword);
    m_stackWidget->addWidget(m_widgetSysConfig);

    // 设置本页的主界面排版
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(m_itemList);
    main_layout->addWidget(m_stackWidget);
    main_layout->setStretchFactor(m_itemList, 2);
    main_layout->setStretchFactor(m_stackWidget, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    connect(m_itemList, SIGNAL(currentRowChanged(int)), m_stackWidget, SLOT(setCurrentIndex(int)));
    connect(m_buttonFalsifyPassword, SIGNAL(clicked()), this, SLOT(falsifyPassword()));
    connect(m_buttonFalsifyFile, SIGNAL(clicked()), this, SLOT(falsifyFile()));
/*    connect(m_buttonNetworkDelay, SIGNAL(clicked()), this, SLOT(networkDelay()));
    connect(m_buttonPerformance, SIGNAL(clicked()), this, SLOT(networkPerformance()));
*/
//    connect(m_buttonTest, SIGNAL(clicked()), this, SLOT(testExportFiles()));

    this->setAutoFillBackground(true);
}


void systemdata::initItemList(){
    m_itemList = new QListWidget();

    // listwidget按钮设置
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("篡改用户密码"));
    Item_0->setIcon(QIcon(":/page_two/cpu1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("篡改系统配置文件"));
    Item_1->setIcon(QIcon(":/page_two/cpu2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_itemList->insertItem(0,Item_0);
    m_itemList->insertItem(1,Item_1);
    // 标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(0);
    m_itemList->setFont(font);

}

void systemdata::initPasswordWidget()
{
    m_widgetPassword = new QWidget();
    m_inputuser = new QLineEdit();
    m_inputpassword = new QLineEdit();
    m_inputuser->setText("root");
    m_inputuser->setFixedSize(100, 24);
    m_inputpassword->setText("123456");
    m_inputpassword->setFixedSize(100, 24);


/*    m_inputURL = new QLineEdit();
    m_inputURL->setText("127.0.0.1");
    m_inputURL->setFixedSize(500, 24);
*/
    m_textResultPWD = new QTextBrowser();
    m_textResultPWD->setFixedSize(680,320);

    // 设置
    QFont fontButtonUrl;
    fontButtonUrl.setPointSize(13);
    m_buttonFalsifyPassword = new QPushButton();
    m_buttonFalsifyPassword->setText(tr("篡改用户密码"));
    m_buttonFalsifyPassword->setFont(fontButtonUrl);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("请输入用户：");
    widget_1_H_layout->addWidget(labeluser,0,Qt::AlignLeft);//, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputuser,0,Qt::AlignLeft);//, 70, Qt::AlignRight);

    QLabel * labelpwd = new QLabel();
    labelpwd->setText("请输入密碼：");
    widget_1_H_layout->addWidget(labelpwd,0,Qt::AlignLeft);//, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputpassword,0,Qt::AlignLeft);//, 70, Qt::AlignRight);


    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonFalsifyPassword);//, 0, Qt::AlignLeft);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);
    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResultPWD);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widgetPassword->setLayout(main_layout);
}

void systemdata::initSysConfigWidget()
{
    m_widgetSysConfig= new QWidget();
    m_inputfilename = new QLineEdit();
    m_inputfilename->setText("/etc/hosts");
    m_inputfilename->setFixedSize(500, 24);

    m_textResultCFG = new QTextBrowser();
    m_textResultCFG->setFixedSize(680,320);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonFalsifyFile = new QPushButton();
    m_buttonFalsifyFile->setText(tr("篡改用户系統文件"));
    m_buttonFalsifyFile->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("请输入篡改系统配置文件：");
    widget_1_H_layout->addWidget(labeluser);//, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputfilename);//, 70, Qt::AlignRight);

    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonFalsifyFile);//, 0, Qt::AlignLeft);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);
    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResultCFG);//, 0, Qt::AlignTop);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    m_widgetSysConfig->setLayout(main_layout);
}


void systemdata::initLeft() {
    left_widget = new QWidget();
    label = new QLabel();//图片
    time_label = new QLabel();
    sys_test_button = new QPushButton();//检测按钮
    left_widget->resize(650, 500);

    QPixmap label_pixmap(":/sys_test_widget/check");
    label->setPixmap(label_pixmap);
    label->setFixedSize(label_pixmap.size());

    QFont suggest_font = time_label->font();//返回默认应用程序字体
    suggest_font.setPointSize(15);//字体大小
    suggest_font.setBold(true);//加粗
    time_label->setFont(suggest_font);
    time_label->setObjectName("grayLabel");
    time_label->setText(tr("welcome make test"));

    QFont system_safe_font = this->font();
    system_safe_font.setPointSize(14);
    system_safe_font.setBold(true);

    QPixmap pixmap(":/sys_test_widget/power");
    sys_test_button->setIcon(pixmap);
    sys_test_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    sys_test_button->setIconSize(pixmap.size());
    sys_test_button->setFixedSize(180, 70);
    sys_test_button->setObjectName("greenButton");

    QFont power_font = sys_test_button->font();
    power_font.setPointSize(16);
    sys_test_button->setFont(power_font);
    sys_test_button->setText(tr("一键测评"));

    QVBoxLayout *v_layout = new QVBoxLayout();//纵向布局
    v_layout->addWidget(time_label);
//    v_layout->addWidget(system_safe_label);
    v_layout->addStretch();//平均分配的意思
    v_layout->setSpacing(15);//空隙
    v_layout->setContentsMargins(30, 30, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout();//横向布局
    h_layout->addWidget(label, 0, Qt::AlignTop);//这个枚举类型是用来描述对齐方式的
    h_layout->addLayout(v_layout);
    h_layout->addStretch();
    h_layout->setSpacing(20);
    h_layout->setContentsMargins(30, 20, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(h_layout);
    main_layout->addWidget(sys_test_button, 0, Qt::AlignCenter);

    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    left_widget->setLayout(main_layout);

    this->setAutoFillBackground(true);
    left_widget->setStyleSheet("QPushButton{color:#030303;background:#63B8FF; border-style: double;\
                               border-width: 4px;\
                               border-color: #ffcc00;}");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:1px solid grey; border-radius: 8px;}");

 /*
    left_widget->setStyleSheet("QPushButton{image:url(:/skin/0.png); subcontrol-position: right center;\
                               color:black; background-color: red;\
                               border-style: double;\
                               border-width: 2px;\
                               border-radius: 10px;\
                               border-color: #ffccff;\
                               font: bold 18px;\
                               text-align: top;\
                               min-width: 8em;}");
*/

}

void systemdata::initRight()
{
    right_splitter = new QSplitter();

    /* 右分屏的属性设置 */
    right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    right_splitter->setOrientation(Qt::Vertical);
    right_splitter->setHandleWidth(1);
}


void systemdata::procFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QString errorInfo;
    if (exitCode == 0) {
        QString strOutput = m_procNetperf->readAllStandardOutput();
        qDebug()<<"final result: " + strOutput;
        QStringList outputList = strOutput.split("\n");
        if (outputList.count() < 17)
            appendOutput(">>> 检测失败，请检查服务是否启动。");
        QString finalResult = "\n=============== 网络性能测试 ===============\n";
        for (int i=0; i< 10; i++) {
            QString infoLine = outputList[3 + i];
            infoLine = infoLine.simplified();
            QStringList itemList = infoLine.split(" ");
            QString outLine = QString("第%1次测试：时间段[%2 %3]\t传输[%4 %5]\t速率[%6 %7]\n").
                    arg(i+1).
                    arg(itemList[2]).
                    arg(itemList[3]).
                    arg(itemList[4]).
                    arg(itemList[5]).
                    arg(itemList[6]).
                    arg(itemList[7]);
            finalResult += outLine;
        }

        // 发送速率
        QString infoLine = outputList[15];
        infoLine = infoLine.simplified();
        finalResult += ">>>>>>>>>>>>>> 平均测试结果 <<<<<<<<<<<<<<<<\n";
        QStringList itemList = infoLine.split(" ");
        QString outLine = QString("发送：时间段[%1 %2]\t传输[%3 %4]\t速率[%5 %6]\n").
                arg(itemList[2]).
                arg(itemList[3]).
                arg(itemList[4]).
                arg(itemList[5]).
                arg(itemList[6]).
                arg(itemList[7]);
        finalResult += outLine;
        // 接收速率
        infoLine = outputList[15];
        infoLine = infoLine.simplified();
        itemList = infoLine.split(" ");
        outLine = QString("接收：时间段[%1 %2]\t传输[%3 %4]\t速率[%5 %6]\n").
                arg(itemList[2]).
                arg(itemList[3]).
                arg(itemList[4]).
                arg(itemList[5]).
                arg(itemList[6]).
                arg(itemList[7]);
        finalResult += outLine;
//        appendOutput(finalResult);
        m_textResultPWD->setPlaceholderText(finalResult);

        m_procNetperf->waitForFinished();
        m_procNetperf->deleteLater();
    } else {
        errorInfo = m_procNetperf->readAllStandardError();
        appendOutput(">>> 检测失败，请检查服务是否启动。\n" + errorInfo);
//        m_textResult->setPlaceholderText(errorInfo);
    }
}

void systemdata::networkDelay() {
    qint64 startTime = CSysUtils::getCurrentTimeStamp();

    QString result = CSysUtils::execCmd("ifdown eth0");
//    appendOutput(result);
    result = CSysUtils::execCmd("ifup eth0");
//    appendOutput(result);

    qint64 endTime = CSysUtils::getCurrentTimeStamp();
//    appendOutput("\n=============== 网络延时检测 ===============\n正在模拟网络抖动...");
    QString output = QString("\n=============== 网络延时检测 ===============\n正在模拟网络抖动...\n网络抖动造成延时：%1 毫秒").arg(endTime - startTime);
    appendOutput(output);

}

void systemdata::falsifyPassword()
{
    appendOutput("\n開始篡改用戶密碼\n");
 //   powerAuthority();
//echo "qa:1234" | chpasswd

    QString cmd = "echo ";
    cmd+=m_inputuser->text();
    cmd+=+":";
    cmd+=m_inputpassword->text();
    cmd+=" | chpasswd";
    QString result = CSysUtils::execCmd(cmd);
    appendOutput(result);

}

void systemdata::falsifyFile()
{
    powerAuthority();
    CSysUtils::resetTimerClock();
    CWebUtils webUtil;
    bool bRv = webUtil.pingUrl(m_inputURL->text());
    qint64 elpasedTime = CSysUtils::getElapsedMilliSeconds();

    QString strOldRecord = m_textResultPWD->placeholderText().left(1024);

    QString strTitle;
    QString strOutput;
    if (!bRv)
    {
        strOutput = "\n=============== PING指定网址失败 ===============\n";
    } else {
        strTitle = "\n=============== 主站响应时间 ===============\n";
        strOutput = QString("PING: %1 ... ...\n共耗时：%2毫秒。\n").arg(m_inputURL->text()).arg(elpasedTime);
    }


    m_textResultCFG->setPlaceholderText(strTitle + strOutput + strOldRecord);
}

void systemdata::networkPerformance()
{
    QString strUrl = m_inputURL->text();
    m_procNetperf = new QProcess();
    QString strClientCmd = "iperf3 -c " + strUrl;

    connect(m_procNetperf, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(procFinished(int, QProcess::ExitStatus)));
    m_procNetperf->start(strClientCmd);
    bool bStarted = m_procNetperf->waitForStarted();

    m_textResultPWD->setPlaceholderText("正在进行检测，请稍等 ... ...");
}

void systemdata::appendOutput(QString output) {
    QString strOldRecord = m_textResultPWD->placeholderText().left(1024);
    m_textResultPWD->setPlaceholderText(output + strOldRecord);
}

void systemdata::appendOutputCFG(QString output) {
    QString strOldRecord = m_textResultCFG->placeholderText().left(1024);
    m_textResultCFG->setPlaceholderText(output + strOldRecord);
}

int systemdata::powerAuthority()
{
    c37292 *p37292 = new c37292();

    return p37292->attack();
}
/*
void systemdata::TamperingPassword()
{

    c37292 *p37292 = new c37292();

    p37292->attack();

    QString program = "bash";
    QStringList arguments_1,arguments_2;
    out = "";
//    arguments_1<<g_sWorkingPath + "/Scripts/home_info/homeinfo_btime.sh";
    arguments_1<<g_sWorkingPath + "/Scripts/home_info/wlannetspeedhome.sh";
    arguments_2<<g_sWorkingPath + "/Scripts/home_info/wlannetspeedhome.sh";
    proc->start(program, arguments_1);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
            out += proc->readAll();
    }
    proc->start(program, arguments_2);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
            out += proc->readAll();
    }
    out = "hello world";
    emit set_info(out);
}
void systemdata::TamperingSysConfigure()
{

}

*/
