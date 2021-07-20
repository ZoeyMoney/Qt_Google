#ifndef SHOW_HOME_DATE_H
#define SHOW_HOME_DATE_H

#include <QWidget>
#include "QMouseEvent"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qgridlayout.h"
#include "QSpacerItem"

namespace Ui {
class Show_Home_Date;
}

class Show_Home_Date : public QWidget
{
    Q_OBJECT

public:
    explicit Show_Home_Date(QWidget *parent = 0);
    ~Show_Home_Date();

    bool m_bPressed;
    QPoint m_point;

private:
    Ui::Show_Home_Date *ui;

    QStringList qss;
    QWidget* main;

    //头部
    QWidget* header;
    QGridLayout* header_layout;
    QLabel* header_title;
    QPushButton* header_close;
    QSpacerItem* header_spacer;
    QPushButton* header_hide;

    //内容
    QWidget* text;
    QLabel* tet;

    void init();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // SHOW_HOME_DATE_H
