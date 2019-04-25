#include "attack.h"
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

//    connect(m_buttonVertical, SIGNAL(clicked()), this, SLOT(xxx()));
//    connect(m_buttonHorizontal, SIGNAL(clicked()), this, SLOT(xxx()));

    this->setAutoFillBackground(true);

}


void attack::initWidget()
{
    m_widget = new QWidget();
    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(680,320);

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
    widget_1_H_layout->addWidget(m_buttonSYN,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->addWidget(m_buttonICMP,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->addWidget(m_buttonLAND,0,Qt::AlignLeft);//, 70, Qt::AlignRight);

    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);

    widget_1_V_layout->addWidget(m_textResult);//, 0, Qt::AlignTop);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widget->setLayout(main_layout);
}

