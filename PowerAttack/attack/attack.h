#ifndef ATTACK_H
#define ATTACK_H

#include <QWidget>
#include "common.h"

#include "syn_flood.h"
#include "icmp_flood.h"

class attack : public QWidget
{
    Q_OBJECT
public:
    explicit attack(QWidget *parent = nullptr);

    void initWidget();
    void appendOutput(QString output);

    unsigned short csum(unsigned short *ptr, int nbytes);
    void oneland(int socketfd, in_addr_t source, u_int16_t sourcePort,in_addr_t destination, u_int16_t destinationPort);
    void doland();
    int dolandex();

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
    class icmp_flood *picmp;



};

#endif // ATTACK_H
