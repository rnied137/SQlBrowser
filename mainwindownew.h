#ifndef MAINWINDOWNEW_H
#define MAINWINDOWNEW_H

#include <QMainWindow>
#include <dbcontroller.h>


namespace Ui {
class MainWindowNew;
}

class MainWindowNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowNew(QWidget *parent=nullptr);
    ~MainWindowNew();


    DbController  * db_controller;
private:
    Ui::MainWindowNew *ui;

signals:
    void connectToServer(QString,QString,QString);
    //void connectToServer();
    void getTablesNames();
    void selectTable(QString);

public slots:
    void connectToServerRequested();
    void on_pushButtonDisconnect_clicked();
    void serverErrorWithConnection(QString message);
    void serverConnected();
    void displayTable(QSqlQueryModel*);
    void fillTableNames(QStringList list);
    void showTableRequested();
};

#endif // MAINWINDOWNEW_H
