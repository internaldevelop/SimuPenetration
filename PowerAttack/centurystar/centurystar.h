#ifndef CENTURYSTAR_H
#define CENTURYSTAR_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QProcess>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextBrowser>

class centurystar : public QWidget
{
    Q_OBJECT
public:
    explicit centurystar(QWidget *parent = nullptr);

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

#endif // CENTURYSTAR_H
