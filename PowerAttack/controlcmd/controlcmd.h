#ifndef CONTROLCMD_H
#define CONTROLCMD_H

//#include "common.h"
#include <QStackedWidget>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "plcqtlib.h"

class controlcmd : public QWidget
{
    Q_OBJECT
public:
    explicit controlcmd(QWidget *parent = nullptr);

public:
//    void initItemList();
    void initWidget();
    void appendOutput(QString output);

signals:

public slots:
    void stopPLC();
    void startPLC();
    void ConnectPlc();

private:

    QStackedWidget*     m_stackWidget;
    QWidget *           m_widget;

    QLineEdit *         m_inputIp;
    QLineEdit *         m_inputPort;

    // 信息框（测试结果）
    QTextEdit *      m_textResult;

    QPushButton *       m_buttonStopPLC;
    QPushButton *       m_buttonStartPLC;

    int port,statotcp,mpi,rack,slot;
    bool stato;
    bool plcok;
    Plcqtlib *conplc;

};

#endif // CONTROLCMD_H
