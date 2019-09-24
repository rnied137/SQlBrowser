#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQueryModel>
#include <QTableView>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QVector>
#include <dbcontroller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector <std::string> vec;
QSqlQuery * query;
QTableView view;
    QSqlDatabase m_db;
        QSqlTableModel *model;
        QSqlQueryModel * table_model;
        const QString PrintAllPersons();
        bool sendQuery( QString queryToDatabase);
       bool addPerson( QString & name);
       bool dynamicQuery(QString &password);
       bool sendRandomQuery();

void odswiezQueryModel();
private slots:
    void on_pushButton_clicked();

    void on_przejdz_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
