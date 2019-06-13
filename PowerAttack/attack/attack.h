#ifndef ATTACK_H
#define ATTACK_H

#include <QWidget>
#include "common.h"

//#include "landattack.h"
#include "syn_flood.h"
#include "icmp_flood.h"
#include "execattackthread.h"
//#include "landattackthread.h"

class attack : public QWidget
{
    Q_OBJECT
public:
    explicit attack(QWidget *parent = nullptr);

    void initWidget();
    void appendOutput(QString output);

    int doland();

    QThread *my_thread;

    ExecAttackThread m_attackThread;
signals:

public slots:

    void processAttackResult(const QString & result);
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
    class icmp_flood *picmp;
//    class landattack *pland;



};

#endif // ATTACK_H
