#ifndef ATTACK_H
#define ATTACK_H

#include <QWidget>
#include "common.h"

#include "syn_flood.h"

class attack : public QWidget
{
    Q_OBJECT
public:
    explicit attack(QWidget *parent = nullptr);

    void initWidget();
    void appendOutput(QString output);

signals:

public slots:

    void syn_flood();
    void icmp_flood();
    void land();

public:
    QStackedWidget*     m_stackWidget;
    QWidget *           m_widget;

    // 信息框（测试结果）
    QTextBrowser *      m_textResult;

    QPushButton *       m_buttonSYN;//SYN Flood攻击
    QPushButton *       m_buttonICMP;//ICMP Flood攻击
    QPushButton *       m_buttonLAND;//LAND攻击

    QLineEdit *         m_inputIp;
    QLineEdit *         m_inputPort;

    class syn_flood *psyn;



};

#endif // ATTACK_H
