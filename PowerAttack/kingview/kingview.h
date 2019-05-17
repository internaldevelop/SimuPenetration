#ifndef KINGVIEW_H
#define KINGVIEW_H

#include <QWidget>
#include "common.h"

class kingview : public QWidget
{
    Q_OBJECT
public:
    explicit kingview(QWidget *parent = nullptr);


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
};

#endif // KINGVIEW_H
