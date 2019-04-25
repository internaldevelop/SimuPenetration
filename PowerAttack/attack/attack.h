#ifndef ATTACK_H
#define ATTACK_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QProcess>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextBrowser>

class attack : public QWidget
{
    Q_OBJECT
public:
    explicit attack(QWidget *parent = nullptr);

    void initWidget();
    void appendOutput(QString output);
signals:

public slots:

public:
    QStackedWidget*     m_stackWidget;
    QWidget *           m_widget;

    // 信息框（测试结果）
    QTextBrowser *      m_textResult;

    QPushButton *       m_buttonSYN;//SYN Flood攻击
    QPushButton *       m_buttonICMP;//ICMP Flood攻击
    QPushButton *       m_buttonLAND;//LAND攻击

};

#endif // ATTACK_H
