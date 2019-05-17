#include "kingview.h"

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

  //    connect(m_buttonVertical, SIGNAL(clicked()), this, SLOT(xxx()));
  //    connect(m_buttonHorizontal, SIGNAL(clicked()), this, SLOT(xxx()));

      this->setAutoFillBackground(true);

}


void kingview::initWidget()
{
    m_widget = new QWidget();

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
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    QLabel * labelutilize = new QLabel();
    labelutilize->setText("CenturyStar9.0 漏洞利用:");
    widget_2_H_layout->addWidget(labelutilize);//, 0, Qt::AlignLeft);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);

    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
//    widget_1_V_layout->addLayout(widget_2_H_layout);
//    widget_1_V_layout->addWidget(m_textResult);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    m_widget->setLayout(main_layout);
}
