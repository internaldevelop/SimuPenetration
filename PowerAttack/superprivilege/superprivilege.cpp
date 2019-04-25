#include "superprivilege.h"
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

superprivilege::superprivilege(QWidget *parent) : QWidget(parent)
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

void superprivilege::initWidget()
{
    m_widget = new QWidget();
    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(680,320);

    // 设置
    QFont fontButton;
    fontButton.setPointSize(13);
    m_buttonVertical= new QPushButton();
    m_buttonVertical->setText(tr("纵向提权"));
    m_buttonVertical->setFont(fontButton);

    m_buttonHorizontal= new QPushButton();
    m_buttonHorizontal->setText(tr("横向提权"));
    m_buttonHorizontal->setFont(fontButton);

    m_buttonOfflineAttack= new QPushButton();
    m_buttonOfflineAttack->setText(tr("离线密码破解"));
    m_buttonOfflineAttack->setFont(fontButton);

    m_buttonOnlineAttack= new QPushButton();
    m_buttonOnlineAttack->setText(tr("在线密码攻击"));
    m_buttonOnlineAttack->setFont(fontButton);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(m_buttonVertical,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->addWidget(m_buttonHorizontal,0,Qt::AlignLeft);//, 70, Qt::AlignRight);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);

    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonOfflineAttack);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonOnlineAttack);//, 0, Qt::AlignLeft);
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
