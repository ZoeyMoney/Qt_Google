#ifndef ADMIN_HOME_H
#define ADMIN_HOME_H

#include <QWidget>
#include "QMouseEvent"
#include <QListWidgetItem>
#include "QList"
#include "qlabel.h"
#include "qdebug.h"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include "qstackedwidget.h"

//切换窗口
#include "Show_Home.h"
#include "Show_Search.h"

namespace Ui {
class Admin_Home;
}

class Admin_Home : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_Home(QWidget *parent = 0);
    ~Admin_Home();

    bool m_bPressed;
    QPoint m_point;

    QWidget* main;
    QWidget* left_list_box;
    QWidget* top_list_box;
    QStringList qss;
    QWidget* icon;
    QLabel* logo;
    QListWidget* list_widget;
    QListWidgetItem* item;
    QWidget* main_show;
    //头像用户名
    QWidget* logo_user;
    QLabel* logo_pix;
    QLabel* hy;
    QLabel* userName;
    QPushButton* exit_user;
    QGridLayout* logo_layout;
    QStackedWidget* stack_main;
    //获取登录的用户名
    QString value;
    void GetName(const QString name);
    //窗口切换
    Show_Home* showHome;
    Show_Search* search;

private:
    Ui::Admin_Home *ui;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void AdminHomeInit();
    void init_home_main();

private slots:
    void list_item_click(QListWidgetItem* item);
    void exit_click();
};

#endif // ADMIN_HOME_H
