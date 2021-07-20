#-------------------------------------------------
#
# Project created by QtCreator 2021-06-01T09:41:16
#
#-------------------------------------------------

QT       += core gui sql network

#network 网络通信用到

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Google
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        home.cpp \
    registered.cpp \
    admin_home.cpp \
    show_home.cpp \
    show_search.cpp \
    show_home_add.cpp \
    show_home_insurance.cpp \
    show_home_date.cpp \
    mymysql.cpp

HEADERS += \
        home.h \
    registered.h \
    admin_home.h \
    show_home.h \
    show_search.h \
    show_home_add.h \
    show_home_insurance.h \
    show_home_date.h \
    mymysql.h

FORMS += \
        home.ui \
    registered.ui \
    admin_home.ui \
    show_home.ui \
    show_search.ui \
    show_home_add.ui \
    show_home_insurance.ui \
    show_home_date.ui

RESOURCES += \
    image.qrc
