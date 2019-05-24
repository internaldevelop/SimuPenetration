#ifndef SUPERPRIVILEGE_H
#define SUPERPRIVILEGE_H

#include "common.h"

class superprivilege : public QWidget
{
    Q_OBJECT
public:
    explicit superprivilege(QWidget *parent = nullptr);

    void initItemList();
    void initWidgetVertical();
    void initWidgetHorizontal();
    void initWidgetOffline();
    void initWidgetOnline();
    void appendOutput(QString output);
    int powerAuthority();

signals:

public slots:
    void verticalPrivilege();
    void horizontalPrivilege();
    void showAllUser();
    void appendOutputH(QString output);
    void appendOutputV(QString output);
    void appendOutputOff(QString output);
    void appendOutputOn(QString output);
    void offlineAttack();
    void onlineAttack();
    void offlineAttackPython();
    void offlineAttackJohn();

private:
    // 左侧功能列表
    QListWidget *       m_itemList;
    QStackedWidget*     m_stackWidget;

    //利用系统漏洞纵向提权
    QWidget *           m_widgetVertical;
    //横向提权
    QWidget *           m_widgetHorizontal;
    //离线密码破解
    QWidget *           m_widgetOffline;
    //在线密码攻击
    QWidget *           m_widgetOnline;

    // 信息框（测试结果）
    QTextEdit *      m_textResultVertical;
    QTextEdit *      m_textResultHorizon;
    QTextEdit *      m_textResultOffline;
    QTextEdit *      m_textResultOnline;

    QLineEdit *         m_inputuser;

    QPushButton *       m_buttonShowUser;//查看显示所有用户
    QPushButton *       m_buttonVertical;//纵向提权
    QPushButton *       m_buttonHorizontal;//横向提权
    QPushButton *       m_buttonOfflineAttack;//离线密码破解
    QPushButton *       m_buttonOnlineAttack;//在线密码攻击

};

#endif // SUPERPRIVILEGE_H
