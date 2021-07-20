#ifndef SHOW_HOME_H
#define SHOW_HOME_H

#include <QWidget>
#include "QHBoxLayout"
#include "qtoolbutton.h"
#include "qpushbutton.h"
#include "qdatetime.h"
#include "qlabel.h"
#include "qgridlayout.h"
#include "QSpacerItem"
#include "qdebug.h"
#include "qtablewidget.h"
#include "qstandarditemmodel.h"
#include "qheaderview.h"
#include "qcheckbox.h"
#include "Show_Home_Add.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QAbstractItemModel>
#include <QTableView>
#include <QMap>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class Show_Home;
}

class Show_Home : public QWidget
{
    Q_OBJECT

public:
    explicit Show_Home(QWidget *parent = 0);
    ~Show_Home();

    QWidget* main;
    int width;
    int height;
    //按钮部分
    QWidget* widget_header;
    QGridLayout* headerLyout;
    QToolButton* addBtn;
    QToolButton* bxBtn;
    QToolButton* qxBtn;
    QPushButton* startBtn;
    QPushButton* orderBtn;
    QSpacerItem* horizontalSpacer;
    QStringList qss;
    //订单人数
    int ddrs = 0;
    //表格
    QWidget* table_widget;
    QTableView* table_view;
    QStandardItemModel* model;
    QSqlQueryModel *query_model;
    QSqlQuery query;
    //存值
    QMap<QString,QCheckBox*> map;
    //选中的值
    QList<QString>list_data;
    //底部按钮
    QWidget* footer_btn;
    QPushButton* confirm;
    QPushButton* cancel;
    QPushButton* del;
    QGridLayout* footer_layout;
    QSpacerItem* footer_spacer;

    Show_Home_Add* show_home_add;
    //初始化大小
    void getSize(int w,int h);

private:
    Ui::Show_Home *ui;

    void showHomeInit();
    void table_view_class();    //初始化表格模型
    void table_view_query_exec();   //初始化表格数据
    QString dataTime();	//封装时间

private slots:
     void add();
     void sendData(QString);
     void confirm_click();	//全部选择
     void cancel_click();	//取消选择
     void del_click();		//删除选中项
     void change_check();
};

#endif // SHOW_HOME_H
