#include "superprivilege.h"
#include "c37292.h"

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
    connect(m_itemList, SIGNAL(currentRowChanged(int)), m_stackWidget, SLOT(setCurrentIndex(int)));

    this->setAutoFillBackground(true);
}

void superprivilege::initItemList(){
    m_itemList = new QListWidget();

    // listwidget按钮设置
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("利用系统漏洞纵向提权"));
    Item_0->setIcon(QIcon(":/page_two/cpu1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("利用系统漏洞横向提权"));
    Item_1->setIcon(QIcon(":/page_two/cpu2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_2 = new QListWidgetItem(tr("离线密码破解"));
    Item_2->setIcon(QIcon(":/page_two/cpu2"));
    Item_2->setTextAlignment(Qt::AlignLeft);
    Item_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_3 = new QListWidgetItem(tr("在线密码攻击"));
    Item_3->setIcon(QIcon(":/page_two/cpu2"));
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
    m_textResultVertical = new QTextBrowser();
    m_textResultVertical->setFixedSize(680,320);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonVertical= new QPushButton();
    m_buttonVertical->setText(tr("纵向提权"));
    m_buttonVertical->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(m_buttonVertical,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
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
    m_textResultHorizon = new QTextBrowser();
    m_textResultHorizon->setFixedSize(680,320);
    m_textResultHorizon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_textResultHorizon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);

    m_buttonShowUser= new QPushButton();
    m_buttonShowUser->setText(tr("列舉显示所有用户"));
    m_buttonShowUser->setFont(fontButton);

    m_inputuser = new QLineEdit();
//    m_inputuser->setText("root");
    m_inputuser->setFixedSize(100, 24);

    m_buttonHorizontal= new QPushButton();
    m_buttonHorizontal->setText(tr("横向提权"));
    m_buttonHorizontal->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
//    widget_1_H_layout->addWidget(m_buttonVertical,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->addWidget(m_buttonShowUser,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    QLabel * labeluser = new QLabel();
    labeluser->setText("请输入横向提权的用户：");
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
    m_textResultOffline = new QTextBrowser();
    m_textResultOffline->setFixedSize(680,320);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);

    m_buttonOfflineAttack= new QPushButton();
    m_buttonOfflineAttack->setText(tr("离线密码破解"));
    m_buttonOfflineAttack->setFont(fontButton);

//    m_buttonOnlineAttack= new QPushButton();
//    m_buttonOnlineAttack->setText(tr("在线密码攻击"));
//    m_buttonOnlineAttack->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(m_buttonOfflineAttack,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
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
    m_textResultOnline = new QTextBrowser();
    m_textResultOnline->setFixedSize(680,320);

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

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(m_buttonOnlineAttack,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
//    widget_1_H_layout->addWidget(m_buttonHorizontal,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
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
    QString strOldRecord = m_textResultVertical->placeholderText().left(1024);
    m_textResultVertical->setPlaceholderText(output + strOldRecord);
}
void superprivilege::appendOutputH(QString output) {
    QString strOldRecord = m_textResultHorizon->placeholderText().left(1024);
    m_textResultHorizon->setPlaceholderText(output + strOldRecord);
}
void superprivilege::appendOutputOff(QString output) {
    QString strOldRecord = m_textResultOffline->placeholderText().left(1024);
    m_textResultOffline->setPlaceholderText(output + strOldRecord);
}
void superprivilege::appendOutputOn(QString output) {
    QString strOldRecord = m_textResultOnline->placeholderText().left(1024);
    m_textResultOnline->setPlaceholderText(output + strOldRecord);
}

void superprivilege::verticalPrivilege()
{
    powerAuthority();
}

void superprivilege::showAllUser()
{
    appendOutputH("\n查看显示所有用户\n");
//    QString cmd = "cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F":" '{ print $1 }'|more ";
//    QString cmd = "cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F\":\" '{ print $1 }'|more ";
//    QString cmd = "cat /etc/passwd |cut -f 1 -d :";
    QString cmd = "cut -d: -f1 /etc/passwd";
    QString result = CSysUtils::execCmd(cmd);
    appendOutputH(result);


}

void superprivilege::horizontalPrivilege()
{
    QString cmd = "echo ";
    cmd+=m_inputuser->text();
    cmd+=+":";
    cmd+="123456";
    cmd+=" | chpasswd";
    QString result = CSysUtils::execCmd(cmd);
    appendOutputH(result);

}

int superprivilege::powerAuthority()
{
    c37292 *p37292 = new c37292();

    return p37292->attack();
}
