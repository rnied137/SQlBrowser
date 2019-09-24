#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QString>
//class QSqlDatabase;

class DbManager
{
public:
    //DbManager();
    DbManager();
     bool sendQuery( QString queryToDatabase);
    bool addPerson( QString & name);
    const QString PrintAllPersons() ;
static bool createConn();
    QSqlDatabase getM_db();


private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

