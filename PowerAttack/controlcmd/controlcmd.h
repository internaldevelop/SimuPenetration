#ifndef CONTROLCMD_H
#define CONTROLCMD_H

#include "common.h"

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

private:

    QStackedWidget*     m_stackWidget;
    QWidget *           m_widget;

    QLineEdit *         m_inputIp;
    QLineEdit *         m_inputPort;

    // 信息框（测试结果）
    QTextEdit *      m_textResult;

    QPushButton *       m_buttonStopPLC;
    QPushButton *       m_buttonStartPLC;

};

#endif // CONTROLCMD_H
