#include "centurystar.h"

centurystar::centurystar(QWidget *parent) : QWidget(parent)
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

void centurystar::initWidget()
{
    m_widget = new QWidget();

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labelprinciple = new QLabel();
    labelprinciple->setText("CenturyStar9.0 漏洞原理:");
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
    widget_1_V_layout->addLayout(widget_2_H_layout);
//    widget_1_V_layout->addWidget(m_textResult);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    m_widget->setLayout(main_layout);
}
