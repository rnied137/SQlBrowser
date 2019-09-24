#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>



DbManager::DbManager( )
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/home/radek/people.db");

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

static bool createConn()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/radek/people.db");

    if (!db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

bool DbManager::addPerson( QString  & name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT into people (name) VALUES (:name)");
    query.bindValue(":name", name);
    if(query.exec())
    {
        success = true;

    }
    else
    {
        qDebug() << "addPerson error:  " << query.lastError();
    }

    return success;
}


bool DbManager::sendQuery(QString queryToDatabase)
{
    bool success = false;
    QSqlQuery query(queryToDatabase);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug()<< "Query failed" << query.lastError();
    }
    return success;

}
 const QString DbManager::PrintAllPersons()

{
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << name;
    }

}

 QSqlDatabase DbManager::getM_db()
 {
     return m_db;
 }
