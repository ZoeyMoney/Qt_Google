#ifndef SHOW_HOME_ADD_H
#define SHOW_HOME_ADD_H

#include <QWidget>
#include "QMouseEvent"
#include "qgridlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "QSpacerItem"
#include "qlineedit.h"
#include "QVBoxLayout"
#include "qdebug.h"
#include "qcalendarwidget.h"
#include "qdatetimeedit.h"
#include "qcombobox.h"
#include <QSqlQuery>

namespace Ui {
class Show_Home_Add;
}

class Show_Home_Add : public QWidget
{
    Q_OBJECT

public:
    explicit Show_Home_Add(QWidget *parent = 0);
    ~Show_Home_Add();

    QWidget* main;
    QStringList qss;

    //头部
    QWidget* title;
    QGridLayout* title_layout;
    QLabel* title_text;
    QPushButton* title_close;
    QSpacerItem* space;

    //表单
    QWidget* from;
    QVBoxLayout* from_layout;
    QLineEdit* name;
    QLineEdit* identity_number;
    QDateEdit* data_of_birth;
    QLineEdit* phone;
    QComboBox* post;
    QLineEdit* add_book;
    QSqlQuery query;
    //提示
    QWidget* footer;
    QLabel* promat;
    QPushButton* add_btn;

    //时间
    //QDateEdit* date;

    bool m_bPressed;
    QPoint m_point;

private:
    Ui::Show_Home_Add *ui;

    void init();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void sendDataList(QString);


private slots:
    void btn_submit();
    bool eventFilter(QObject*, QEvent*);
};

#endif // SHOW_HOME_ADD_H
