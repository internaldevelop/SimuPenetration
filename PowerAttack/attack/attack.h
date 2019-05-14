#ifndef ATTACK_H
#define ATTACK_H

#include <QWidget>
#include "common.h"

#include "syn_flood.h"
#include "icmp_flood.h"
#include "execattackthread.h"

//class My_Obj_attack: public QObject
//{
//    Q_OBJECT
//public:
//    explicit My_Obj_attack();

//protected:
//    QProcess *proc;
//    QString out;
//    QTimer *timer;
//signals:
//    void send_appendOutput(QString str);
//protected slots:
//    void start_timer();
//};

class attack : public QWidget
{
    Q_OBJECT
public:
    explicit attack(QWidget *parent = nullptr);

    void initWidget();
    void appendOutput(QString output);

    int doland();
//    My_Obj_attack *My_Obj_attack_object;//netspeed
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



};

#endif // ATTACK_H
