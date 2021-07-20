#include "mymysql.h"

myMysql::myMysql(QObject *parent) : QObject(parent)
{

//    openMysql();
}

bool myMysql::openMysql()
{
//    db = QSqlDatabase::addDatabase("QMYSQL");


    //这里报错了
    //QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed.
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName("localhost");
    db.setDatabaseName("google_admin");
    db.setUserName("root");
    db.setPassword("root");

//    qDebug() << db.open();

    if(!db.open())
    {
        QMessageBox::warning(NULL,"数据库出错",db.lastError().text(),QMessageBox::Cancel);
        return false;
    }

    return true;
}
