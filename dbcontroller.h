#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H
#include <QString>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQueryModel>

class DbController:public QObject
{
    Q_OBJECT
public:

    DbController(QObject * parent);
    QSqlDatabase db;

    QSqlQueryModel * selectTable(QString name);

public:
    bool connectToServerSqlite(QString = NULL, QString = NULL, QString=NULL);
    bool connectToServerPostgress(QString = NULL, QString=NULL, QString=NULL);
    bool checkIfTableExists(QString);
    bool checkIfConnected();
public slots:

    void connectToServerRequested(QString engine, QString server, QString database);
    //void getTableNamesRequested(QString table);
   void getTablesNamesRequested();
   void selectTableRequested(QString table);

signals:
    void serverErrorWithConnection(QString);
    void serverConnected();
    void tableSelected(QSqlQueryModel *);
    void gotTablesNames(QStringList);
};

#endif // DBCONTROLLER_H
