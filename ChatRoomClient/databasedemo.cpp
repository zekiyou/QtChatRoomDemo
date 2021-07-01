#include "databasedemo.h"

DataBaseDemo::DataBaseDemo()
{
    initDataBase();
}

void DataBaseDemo::initDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("MyDataBase.db");
    if (!db.open()) {
        qDebug() << "Error: Failed to connect database." ;
    }
    else {
        qDebug() << "Succeed to connect database." ;
    }

    //创建表格
    QSqlQuery sql_query(db);
    if (!sql_query.exec("create table User(Username varchar(20), Password varchar(20))")) {
        qDebug() << "Error: Fail to create table.";
    }
    else {
        qDebug() << "Table created!";
    }

    insertUser("yzq","123456");
    insertUser("YZQ","123456");
}

bool DataBaseDemo::searchUserData(QString user, QString pwd)
{
    //查询数据
    QSqlQuery sql_query(db);
    sql_query.exec("select * from User where Username = '"+user+"' ");
    if (!sql_query.exec()) {

        qDebug()<<"Error: Fail to searchUserData";
        return false;
    }
    else {
        sql_query.next();
        QString m_user = sql_query.value(0).toString();
        QString m_pwd = sql_query.value(1).toString();
        qDebug()<<m_user;
        qDebug()<<m_pwd;

        if (m_pwd == pwd) {
            qDebug()<<"serchUserdata successfully";
            return true;
        }

        return false;
    }

}


bool DataBaseDemo::insertUser(QString user, QString pwd)
{
    //插入数据
    QSqlQuery sql_query(db);
    if (!sql_query.exec("INSERT INTO User VALUES('"+user+"','"+pwd+"')")) {
        qDebug() << "Error: Fail to insert data";
        return false;
    }
    else {
        qDebug() << "inserted successfully!";
        return true;
    }
}
