#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include <QWidget>
#include <QDialog>
#include <QThread>
#include <QPushButton>
#include <QSplitter>
#include <QLabel>
#include <QTextBrowser>
#include <QProgressBar>
#include <QProcess>
#include <QTimer>
#include <QStringList>
#include "show_percent_page.h"
#include "net_speed.h"

class systemdata : public QWidget
{
    Q_OBJECT
public:
    explicit systemdata(QWidget *parent = nullptr);

protected:

    QSplitter *main_splitter;
    /*左侧窗口*/
    QWidget *left_widget;
    QLabel *label;
    QLabel *time_label;

    QPushButton *TamperingPwd_button; //篡改用戶密碼
    QPushButton *TamperingSysCfg_button; //篡改系統配置

    QProcess *proc;
    QString out;
    void home_btime();
    QSplitter *right_splitter;

//    User_Msg *right_top_widget;

    show_percent_page *right_center_widget;

    Net_Speed *right_bottom_widget;

private:
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightBottom();
    void initRight();


signals:
        void go_sys_test_page();
        void set_info(QString str);

public slots:
        void TamperingPassword();
        void TamperingSysConfigure();
};

#endif // SYSTEMDATA_H
