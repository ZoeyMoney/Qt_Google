#ifndef REGISTERED_H
#define REGISTERED_H

#include <QWidget>
#include "qpushbutton.h"
#include "qpropertyanimation.h"
#include "qdebug.h"
#include "QMouseEvent"
#include "qtoolbutton.h"
#include "QHBoxLayout"
#include "qlineedit.h"
#include "qlabel.h"
#include "QFormLayout"
#include "QTime"
#include "qcheckbox.h"
#include "mymysql.h"
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class Registered;
}

class Registered : public QWidget
{
    Q_OBJECT

public:
    explicit Registered(QWidget *parent = 0);
    ~Registered();

private:
    Ui::Registered *ui;

    bool m_bPressed;
    QPoint m_point;

    myMysql *mymysql;

    QWidget* main;
    QStringList qss;
    QPushButton* close;
    QToolButton* login_return;
    QWidget* header_icon;
    QLabel* icon;
    //from
    QWidget* vb;
    QLineEdit* email;
    QLineEdit* userName;
    QLineEdit* phone;
    QLineEdit* pwd;
    QLineEdit* configPwd;
    QLineEdit* code;
    QPushButton* codeRadoum;
    int IntCode;
    //提示语
    QLabel* prompt;
    //登录
    QPushButton* login;

    void registered_init();

    void time_init();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    bool btn_close_anmation();
    void btn_close();
    void login_ites();
    void create_user();
};

#endif // REGISTERED_H
