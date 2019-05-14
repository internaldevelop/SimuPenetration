#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "common.h"

class systemdata : public QWidget
{
    Q_OBJECT
public:
    explicit systemdata(QWidget *parent = nullptr);

public:
    void initItemList();
    void initPasswordWidget();
    void initSysConfigWidget();

private:
    // 左侧功能列表
    QListWidget *       m_itemList;
    QStackedWidget*     m_stackWidget;

    //篡改用户密码
    QWidget *           m_widgetPassword;
    //篡改系统配置文件
    QWidget *           m_widgetSysConfig;

    QLineEdit *         m_inputuser;
    QLineEdit *         m_inputpassword;
    QLineEdit *         m_inputinsert;

    QLineEdit *         m_inputfilename;

    //篡改
    QPushButton *       m_buttonFalsifyPassword;
    QPushButton *       m_buttonFalsifyFile;
    QPushButton *       m_buttonOpenFile;

//    // 测试网络性能的widget
//    QWidget *           m_widgetBandWidth;
//    // URL输入框
//    QLineEdit *         m_inputURL;
//    // 测试URL访问的按钮
//    QPushButton *       m_buttonAccessURL;
//    // 测试ping通网址的按钮
//    QPushButton *       m_buttonPingURL;
//    // 测试网卡性能的按钮
//    QPushButton *       m_buttonPerformance;
//    // 网络延时检测的按钮
//    QPushButton *       m_buttonNetworkDelay;
    // 信息框（测试结果）
    QTextBrowser *      m_textResultPWD;
    QTextBrowser *      m_textResultCFG;
    // 测试网络性能的进程
    QProcess *          m_procNetperf;

    // 展示性能分析图表的widget
//    SystemPerfReport *    m_widgetAnalyzeReport;
    // 临时测试按钮
    QPushButton *       m_buttonTest;

protected slots:
    void falsifyPassword();
    void falsifyFile();
    void showFileinfo();

    void appendOutput(QString output);
    void appendOutputCFG(QString output);

public:
    int powerAuthority();
    void initLeft();
    void initRight();

private:
    QWidget *       left_widget;
    QLabel *        label;
    QLabel *        time_label;
    QPushButton *   sys_test_button;
    QSplitter *     main_splitter;
    QSplitter *     right_splitter;
};

#endif // SYSTEMDATA_H
