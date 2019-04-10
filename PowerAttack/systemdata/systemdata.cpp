#include "systemdata.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QtTest/QtTest>
#include "common.h"
#include "net_speed.h"

systemdata::systemdata(QWidget *parent) : QWidget(parent)
{
    this->initLeft();
    this->initRightTop();
    this->initRightCenter();
    this->initRightBottom();
    this->initRight();

    main_splitter = new QSplitter();
    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//可自行增大和收缩
    main_splitter->setOrientation(Qt::Horizontal);//Qt::Vertical and Qt::Horizontal   qspliter的取向
    main_splitter->setHandleWidth(4); //设置分界线的宽度
    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

    /* 右分屏的属性设置 */
    right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    right_splitter->setOrientation(Qt::Vertical);
    right_splitter->setHandleWidth(1);
/*   加载widget  */
//    right_top_widget->setFixedSize(250, 80);
    right_center_widget->setFixedSize(250, 340);
    right_bottom_widget->setFixedSize(250, 50);
//    right_splitter->addWidget(right_top_widget);
    right_splitter->addWidget(right_center_widget);
//    right_splitter->addWidget(right_bottom_widget);

    main_splitter->addWidget(left_widget);
    main_splitter->addWidget(right_splitter);

    //禁止拖动
    for(int i = 0; i<right_splitter->count();i++)
    {
        QSplitterHandle *handle = right_splitter->handle(i);
        handle->setEnabled(false);
    }

    for(int i = 0; i<main_splitter->count();i++)
    {
        QSplitterHandle *handle = main_splitter->handle(i);
        handle->setEnabled(false);
    }
    proc = new QProcess();
    out = "";


    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);//空隙
    main_layout->setContentsMargins(0, 0, 0, 0);/*这是设置一个元素所有外边距的宽度，
                                                                                    或者设置各边上外边距的宽度 */

    this->setLayout(main_layout);//将main_layout设置为当前widget的布局

    //    connect(sys_test_button, SIGNAL(clicked()), this, SIGNAL(go_sys_test_page()));

    connect(TamperingPwd_button, SIGNAL(clicked()), this, SLOT(TamperingPassword()));
    connect(TamperingSysCfg_button,SIGNAL(clicked()),this,SLOT(TamperingSysConfigure()));

    this->home_btime();
}

void systemdata::TamperingPassword()
{
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


void systemdata::initLeft()
{
    left_widget = new QWidget();
    label = new QLabel();//图片
    time_label = new QLabel();
    TamperingPwd_button = new QPushButton();//篡改用戶密碼按钮
    TamperingSysCfg_button = new QPushButton();//篡改系統配置
    left_widget->resize(650, 500);

//    QPixmap label_pixmap(":/sys_test_widget/check");
//    label->setPixmap(label_pixmap);
//    label->setFixedSize(label_pixmap.size());

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
    TamperingPwd_button->setIcon(pixmap);
    TamperingPwd_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    TamperingPwd_button->setIconSize(pixmap.size());
    TamperingPwd_button->setFixedSize(180, 70);
    TamperingPwd_button->setObjectName("greenButton");

    QFont power_font = TamperingPwd_button->font();
    power_font.setPointSize(16);
    TamperingPwd_button->setFont(power_font);
    TamperingPwd_button->setText(tr("篡改用户密码"));

    QPixmap pixmapsyscfg(":/sys_test_widget/power");
    TamperingSysCfg_button->setIcon(pixmapsyscfg);
    TamperingSysCfg_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    TamperingSysCfg_button->setIconSize(pixmapsyscfg.size());
    TamperingSysCfg_button->setFixedSize(180, 70);
    TamperingSysCfg_button->setObjectName("greenButton");

    TamperingSysCfg_button->setFont(power_font);
    TamperingSysCfg_button->setText(tr("篡改系統配置"));

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
    main_layout->addWidget(TamperingPwd_button, 0, Qt::AlignCenter);
    main_layout->addWidget(TamperingSysCfg_button, 0, Qt::AlignCenter);

    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    left_widget->setLayout(main_layout);

    this->setAutoFillBackground(true);
    left_widget->setStyleSheet("QPushButton{color:#030303;background:#63B8FF; border-style: double;\
                               border-width: 4px;\
                               border-color: #ffcc00;}");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:1px solid grey; border-radius: 8px;}");

}

void systemdata::home_btime()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<g_sWorkingPath + "/Scripts/home_info/homeinfo_btime.sh";
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
            out += proc->readAll();
    }
    time_label->setText(out);
}
void systemdata::initRight()
{
    right_splitter = new QSplitter();
}

void systemdata::initRightTop()
{
//    right_top_widget = new User_Msg();

}
void systemdata::initRightCenter()
{
    right_center_widget = new show_percent_page();
}

void systemdata::initRightBottom()
{
//    right_bottom_widget = new QWidget();
    right_bottom_widget = new Net_Speed();
}
