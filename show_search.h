#ifndef SHOW_SEARCH_H
#define SHOW_SEARCH_H

#include <QWidget>
#include "qpushbutton.h"
#include "qdebug.h"
#include "qlabel.h"
#include "qgridlayout.h"
#include "qlineedit.h"
#include "qcombobox.h"
#include "QSpacerItem"
#include "QMouseEvent"
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlTableModel>

namespace Ui {
class Show_Search;
}

class Show_Search : public QWidget
{
    Q_OBJECT

public:
    explicit Show_Search(QWidget *parent = 0);
    ~Show_Search();

    //窗口大小
    int width;
    int height;
    void getResize(int w, int h);

    //样式
    QStringList qss;

    //窗口
    QWidget* main;
    //查询条件
    QWidget* header;
    QLineEdit* search;
    QComboBox* combobox;
    QPushButton* submit;
    QGridLayout* header_layout;
    QSpacerItem* space;
    //表格
    QTableView* table;
    QSqlQuery query;
    QSqlQueryModel *model;
    QStringList listText;
    QStandardItemModel *itemModel;
    QSqlTableModel* tablemodel;
    QSqlRecord rec;

private:
    Ui::Show_Search *ui;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void search_init();		//初始化内容
    void table_title_init();    //表格模型属性初始化
    void table_data_init(); //表格数据初始化
    void table_remove();       //清空表


private slots:
    void search_click();
};

#endif // SHOW_SEARCH_H
