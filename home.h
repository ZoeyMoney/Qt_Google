#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "qdebug.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "QMouseEvent"
#include "qgraphicsview.h"
#include "qtimer.h"
#include "qpropertyanimation.h"
#include "QDesktopWidget"
#include "QRegExpValidator"
#include "mymysql.h"
#include <QSqlQuery>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

    QStringList qss;

private:
    Ui::Home *ui;
    //连接数据库、与数据状态
    myMysql* mysql;
    bool flag;

    QWidget* main;
    QWidget* header_icon;
    QLabel* icon;
    QLineEdit* user;
    QLineEdit* pwd;
    QWidget* from;
    QPushButton* login;
    QPushButton* close;
    QPushButton* create;
    QLabel* prompt;

    bool m_bPressed;
    QPoint m_point;

    void win_init();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);



private slots:

    bool btn_close_anmation();
    void btn_close();
    void login_click();
    void create_ites();
};

#endif // HOME_H
