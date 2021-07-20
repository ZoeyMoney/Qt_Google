#ifndef MYMYSQL_H
#define MYMYSQL_H

#include <QObject>
#include "QSqlDatabase"
#include "QSqlError"
#include <QDebug>
#include <QMessageBox>

class myMysql : public QObject
{
    Q_OBJECT
public:
    explicit myMysql(QObject *parent = nullptr);

    QSqlDatabase db;

    bool openMysql();

signals:

public slots:
};

#endif // MYMYSQL_H
