#include "home.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/google.png"));
    QFont font;
    font.setFamily("微软雅黑");
    a.setFont(font);
    Home w;
    w.show();

    return a.exec();
}
