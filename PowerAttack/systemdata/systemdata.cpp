#include "systemdata.h"
#include "c37292.h"

#include <qfile.h>
#include <qtextstream.h>
#include <QFileDialog>
#include "common.h"

QString getcurrenttime();
QString getcurrenttime()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
    return current_date;
}

systemdata::systemdata(QWidget *parent) : QWidget(parent)
{
//    this->initLeft();
//    this->initRightTop();
//    this->initRightCenter();
//    this->initRightBottom();
//    this->initRight();

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
    connect(m_buttonOpenFile, SIGNAL(clicked()), this, SLOT(showFileinfo()));

//    connect(m_textResultCFG, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));
//    connect(m_textResultPWD, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));


    this->setAutoFillBackground(true);
}


void systemdata::initItemList(){
    m_itemList = new QListWidget();

    // listwidget按钮设置
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("篡改用户密码"));
    Item_0->setIcon(QIcon(":/page1/pwd"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("篡改系统配置文件"));
    Item_1->setIcon(QIcon(":/page1/file"));
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
    m_inputuser->setText("lvjz");
    m_inputuser->setFixedSize(200, 24);
    m_inputpassword->setText("123456");
    m_inputpassword->setFixedSize(200, 24);


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
    labelpwd->setText("请输入密码：");
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
    m_inputfilename->setText("/etc/hosts");//("/home/ljz/txt");
    m_inputfilename->setFixedSize(360, 24);

    m_textResultCFG = new QTextEdit();
    m_textResultCFGNew = new QTextEdit();
    m_textResultCFGLOG = new QTextEdit();
    m_textResultCFG->setFixedSize(340,300);
    m_textResultCFGNew->setFixedSize(340,300);
    m_textResultCFGLOG->setFixedSize(690,80);

    m_textResultCFGNew->setReadOnly(true);
    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);

    m_buttonOpenFile = new QPushButton();
    m_buttonOpenFile->setText(tr("查看文件内容"));
    m_buttonOpenFile->setFont(fontButton);

    m_buttonFalsifyFile = new QPushButton();
    m_buttonFalsifyFile->setText(tr("篡改用户文件"));
    m_buttonFalsifyFile->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("请输入篡改文件路径：");
    widget_1_H_layout->addWidget(labeluser);//, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputfilename);//, 70, Qt::AlignRight);
    widget_1_H_layout->addWidget(m_buttonOpenFile);//, 70, Qt::AlignRight);

//    QHBoxLayout *widget_3_H_layout = new QHBoxLayout();
//    QLabel * labelinsert = new QLabel();
//    labelinsert->setText("输入插入的数据：");
//    widget_3_H_layout->addWidget(labelinsert);//, 0, Qt::AlignLeft);
//    widget_3_H_layout->addWidget(m_inputinsert);//, 70, Qt::AlignRight);
//    widget_3_H_layout->setContentsMargins(20, 5, 20, 5);

    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonFalsifyFile);//, 0, Qt::AlignLeft);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);

    QHBoxLayout *widget_3_H_layout = new QHBoxLayout();
    widget_3_H_layout->addWidget(m_textResultCFGNew);//, 70, Qt::AlignRight);
    widget_3_H_layout->addWidget(m_textResultCFG);//, 70, Qt::AlignRight);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addLayout(widget_3_H_layout);
    widget_1_V_layout->addWidget(m_textResultCFGLOG);//, 0, Qt::AlignTop);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    m_widgetSysConfig->setLayout(main_layout);
}


void systemdata::initLeft() {
//    left_widget = new QWidget();
//    label = new QLabel();//图片
//    time_label = new QLabel();
//    sys_test_button = new QPushButton();//检测按钮
//    left_widget->resize(650, 500);

//    QPixmap label_pixmap(":/sys_test_widget/check");
//    label->setPixmap(label_pixmap);
//    label->setFixedSize(label_pixmap.size());

//    QFont suggest_font = time_label->font();//返回默认应用程序字体
//    suggest_font.setPointSize(15);//字体大小
//    suggest_font.setBold(true);//加粗
//    time_label->setFont(suggest_font);
//    time_label->setObjectName("grayLabel");
//    time_label->setText(tr("welcome make test"));

//    QFont system_safe_font = this->font();
//    system_safe_font.setPointSize(14);
//    system_safe_font.setBold(true);

//    QPixmap pixmap(":/sys_test_widget/power");
//    sys_test_button->setIcon(pixmap);
//    sys_test_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
//    sys_test_button->setIconSize(pixmap.size());
//    sys_test_button->setFixedSize(180, 70);
//    sys_test_button->setObjectName("greenButton");

//    QFont power_font = sys_test_button->font();
//    power_font.setPointSize(16);
//    sys_test_button->setFont(power_font);
//    sys_test_button->setText(tr("一键测评"));

//    QVBoxLayout *v_layout = new QVBoxLayout();//纵向布局
//    v_layout->addWidget(time_label);
////    v_layout->addWidget(system_safe_label);
//    v_layout->addStretch();//平均分配的意思
//    v_layout->setSpacing(15);//空隙
//    v_layout->setContentsMargins(30, 30, 0, 0);

//    QHBoxLayout *h_layout = new QHBoxLayout();//横向布局
//    h_layout->addWidget(label, 0, Qt::AlignTop);//这个枚举类型是用来描述对齐方式的
//    h_layout->addLayout(v_layout);
//    h_layout->addStretch();
//    h_layout->setSpacing(20);
//    h_layout->setContentsMargins(30, 20, 0, 0);

//    QVBoxLayout *main_layout = new QVBoxLayout();
//    main_layout->addLayout(h_layout);
//    main_layout->addWidget(sys_test_button, 0, Qt::AlignCenter);

//    main_layout->addStretch();
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);

//    left_widget->setLayout(main_layout);

//    this->setAutoFillBackground(true);
//    left_widget->setStyleSheet("QPushButton{color:#030303;background:#63B8FF; border-style: double;\
//                               border-width: 4px;\
//                               border-color: #ffcc00;}");
//    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:1px solid grey; border-radius: 8px;}");

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

void systemdata::showFileinfo()
{
    QString cmd = "cat ";
    cmd+=m_inputfilename->text();
    QString result = CSysUtils::execCmd(cmd);
//    appendOutputCFG(result);
//    m_textResultCFG->setPlaceholderText(result);
    m_textResultCFG->setPlainText(result);
    m_textResultCFGNew->setPlainText(result);

    appendOutputCFGLOG("文件打开成功，左侧为原始文件，右侧文件内容可编辑，修改后按篡改操作保存修改内容.");
}


void systemdata::initRight()
{
//    right_splitter = new QSplitter();

//    /* 右分屏的属性设置 */
//    right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    right_splitter->setOrientation(Qt::Vertical);
//    right_splitter->setHandleWidth(1);
}

void systemdata::falsifyPassword()
{
    appendOutput("开始篡改用户密码");
 //   powerAuthority();
//echo "qa:1234" | chpasswd

//    QString cmd = "echo ";
//    cmd+=m_inputuser->text();
//    cmd+=+":";
//    cmd+=m_inputpassword->text();
//    cmd+=" | chpasswd";
//    QString result = CSysUtils::execCmd(cmd);
//    appendOutput(result);

    QProcess proc;
    QString cmd = "echo";
    QStringList paramsList;
    paramsList.append(m_inputuser->text()+":"+m_inputpassword->text()+"| chpasswd");
//    paramsList.append("| chpasswd");
    proc.start(cmd,paramsList);

    // 读取命令返回结果
    proc.waitForFinished();
    QString usageInfo = proc.readAllStandardOutput();
    appendOutput(usageInfo);

    QString msg = "用户:"+m_inputuser->text()+"密码:"+m_inputpassword->text()+"篡改成功.";
    appendOutput(msg);

}

void systemdata::falsifyFile()
{
//    powerAuthority();

    QString txt = m_textResultCFG->toPlainText();
    QFile file(m_inputfilename->text());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(txt.toUtf8());
    file.close();

    appendOutputCFGLOG("\n已成功篡改用户文件.\n");

}


void systemdata::appendOutput(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultPWD->toPlainText().left(1024);
    m_textResultPWD->setPlainText(strOldRecord + output);

}

void systemdata::appendOutputCFG(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultCFG->toPlainText().left(1024);
    m_textResultCFG->setPlainText(strOldRecord + output);
}

void systemdata::appendOutputCFGNEW(QString output) {
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultCFGNew->toPlainText().left(1024);
    m_textResultCFGNew->setPlainText(strOldRecord + output);
}

void systemdata::appendOutputCFGLOG(QString output) {
//    QString strOldRecord = m_textResultCFGLOG->toPlainText().left(1024);
//    m_textResultCFGLOG->setPlainText(strOldRecord + "\n" + output);
    output = "["+getcurrenttime()+"] "+output+"\n";
    QString strOldRecord = m_textResultCFGLOG->toPlainText().left(1024);
    m_textResultCFGLOG->setPlainText(strOldRecord + output);

}

int systemdata::powerAuthority()
{
    c37292 *p37292 = new c37292();

    return p37292->attack();
}

