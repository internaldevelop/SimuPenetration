#ifndef ExecAttackThread_H
#define ExecAttackThread_H

#include <QMutex>
#include <QProcess>
#include <QThread>
#include <QWaitCondition>

#include "syn_flood.h"
#include "icmp_flood.h"

class ExecAttackThread : public QThread
{
    Q_OBJECT

public:
    explicit ExecAttackThread(QObject *parent = nullptr);
    ~ExecAttackThread() Q_DECL_OVERRIDE;

    void startSlave();
    void execScipts(QString script);
    void execAttack(QString ip,QString port,int itype);
    void stopAttack(int itype);

signals:
    void attackResult(const QString & result);

private:
    void run() Q_DECL_OVERRIDE;

    // 轮询间隔时间
//    int         m_pollingInterval = 5000;
    QMutex          m_mutex;
    bool            m_quit = false;
    QProcess *      m_procShell;
    bool            m_bExecShell = false;
    QString         m_script;
    QString         m_result;

    QString         m_ip;
    QString         m_port;
    int             m_type;

    class syn_flood *psyn;
    class icmp_flood *picmp;

//    int m_waitTimeout = 0;

};

#endif // ExecAttackThread_H
