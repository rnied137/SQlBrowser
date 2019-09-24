#include "dbcontroller.h"
#include <QDebug>
#include <QSqlQuery>
#include <QList>

DbController::DbController(QObject * parent):QObject(parent)
{

}

void DbController::connectToServerRequested(QString engine, QString server, QString database)
{
    db = QSqlDatabase();
    db.removeDatabase("example-connection");

    if (engine == "sqlite")
    {

        db=QSqlDatabase::addDatabase("QSQLITE", "example-connection");
        qDebug() << "Probuje dodac sqlite database";
    }
    else if (engine == "postgress")
    {
        db = QSqlDatabase::addDatabase("postgress","example-connection");
        qDebug() << " Probuje wybrac postgressa";
    }
    else {
        //wyzwala sygnal dla connecta z mainwindow
        emit serverErrorWithConnection("Unknown database engine");

        qDebug() << "Wystapil blad przy wyborze engina";
        return;
    }

    bool connection_succesfull;

    if (engine == "sqlite")
    {
        connection_succesfull = connectToServerSqlite(server, database);
    }
    else if(engine == "postgress")
    {
        connection_succesfull = connectToServerPostgress(server,database);
    }
    else
    {
        emit serverErrorWithConnection("Bład przy podlaczaniu jednej z baz (Postgress lub SQLIte");
    }

    if (connection_succesfull)
    {
        qDebug() << "Polaczono z serwerem";
        emit  serverConnected();
    }
    else
    {
        emit serverErrorWithConnection("Blad w ostatnim kroku polaczenia");
    }


}

bool DbController::connectToServerSqlite(QString server, QString database, QString)
{
    //db.setHostName(server);
    db.setDatabaseName(database);
    //db.setDatabaseName
    //m_db.setDatabaseName("/home/radek/people.db");
}

bool DbController::connectToServerPostgress(QString server, QString database, QString)
{
    db.setHostName(server);
    db.setDatabaseName(database);
}

void DbController::selectTableRequested(QString table)
{
    QSqlQueryModel * model = selectTable(table);
    qDebug() << "table z wybranej tabeli to " << table;
    emit tableSelected(model);
}

QSqlQueryModel * DbController::selectTable(QString name)
{
    QSqlQueryModel * model = new QSqlQueryModel;

    qDebug() << "name z selecttable ma wartosc" << name;
    qDebug() << "db selecttable ma wartosc" << db;

    model->setQuery("SELECT * FROM " + name);

    return model;
}

void DbController::getTablesNamesRequested()
{
    qDebug() << "odpalam szukanie w tabeli";
    db = QSqlDatabase();

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/radek/people.db");


    if (!db.open())
    {
        qDebug() << "baza nie otworzona";
return;

    }
    else
    {
    qDebug() << "Baza sie poprawnie otworzyla";
    }


    QList<QString> db_list;
QStringList list;
    QSqlQuery query("Select name FROM sqlite_master WHERE type='table'");
    if(query.exec())
    {
        while(query.next())
        {

            QString val;
            val=query.value(0).toString();
            list.append(val);
            db_list.append(QString(val));

        }
    }
    else
    {
        qDebug()<< "Query failed";

    }




qDebug () << "list ma" << list;
emit gotTablesNames(db.tables());
//emit gotTablesNames((db_list));
//emit gotTablesNames(list);
}
