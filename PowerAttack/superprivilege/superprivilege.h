#ifndef SUPERPRIVILEGE_H
#define SUPERPRIVILEGE_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QProcess>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextBrowser>
class superprivilege : public QWidget
{
    Q_OBJECT
public:
    explicit superprivilege(QWidget *parent = nullptr);

    void initWidget();
    void appendOutput(QString output);

signals:

public slots:

public:
    QStackedWidget*     m_stackWidget;
    QWidget *           m_widget;

    // 信息框（测试结果）
    QTextBrowser *      m_textResult;

    QPushButton *       m_buttonVertical;//纵向提权
    QPushButton *       m_buttonHorizontal;//横向提权
    QPushButton *       m_buttonOfflineAttack;//离线密码破解
    QPushButton *       m_buttonOnlineAttack;//在线密码攻击

};

#endif // SUPERPRIVILEGE_H
