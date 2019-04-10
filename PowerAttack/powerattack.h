#ifndef POWERATTACK_H
#define POWERATTACK_H

#include <QMainWindow>
#include "drop_shadow_widget.h"
#include <QStackedWidget>
#include <QTimer>
#include <QDateTime>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include "title_widget.h"
#include "boot_start_time.h"
#include "buttom_widget.h"
#include "main_menu.h"
//#include "Pages/cpagesysperformance.h"

#include "systemdata/systemdata.h"

class PowerAttack : public DropShadowWidget
{
    Q_OBJECT
signals:

private slots:
    void turnPage(int current_page);
//    void show_start_time();
//    void hide_start_time();
//    void show_input_pwd_widget();
    void change_skin(QString new_skin_name);
//    void go_sys_test_page();
    void show_main_menu();

private:
    QTimer *tmr_show_start_time;
    QTimer *tmr_hide_start_time;
    QTimer *tmr_input_pwd;

    QStackedWidget *stacked_widget;
    TitleWidget *title_widget;
    Boot_Start_Time *start_time_widget;

    Buttom_Widget *button_widget;
    QSystemTrayIcon *myTrayIcon;
    QAction *restoreWinAction,*quitAction;
    QMenu *myMenu;
    QString skin_name;//主窗口背景图片的名称
    Main_Menu *main_menu;
    void createMenu();
    void showNormal();

    systemdata *dlgsystemdata;

    // ==========================================================
    void  initGlobalVars();
public:
    PowerAttack(QWidget *parent = 0);
    ~PowerAttack();
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // POWERATTACK_H
