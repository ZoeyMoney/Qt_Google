#ifndef SHOW_HOME_INSURANCE_H
#define SHOW_HOME_INSURANCE_H

#include <QWidget>
#include "QMouseEvent"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "QSpacerItem"
#include "qline.h"

namespace Ui {
class Show_Home_Insurance;
}

class Show_Home_Insurance : public QWidget
{
    Q_OBJECT

public:
    explicit Show_Home_Insurance(QWidget *parent = 0);
    ~Show_Home_Insurance();

    bool m_bPressed;
    QPoint m_point;
    QStringList qss;


private:
    Ui::Show_Home_Insurance *ui;

    QWidget* main;

    //头部
    QWidget* header;
    QGridLayout* header_layout;
    QPushButton* header_close;
    QLabel* header_title;
    QSpacerItem* header_spacer;

    //内容
    QWidget* text;
    QLabel* text_label;

    void insurance_init();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // SHOW_HOME_INSURANCE_H
