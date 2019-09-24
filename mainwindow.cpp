#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <QDebug>
#include <iostream>
#include <dialog.h>
#include <QMessageBox>
#include <error.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    // PrintAllPersons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //QSqlQuery * query=new QSqlQuery(m_db);
    //QSqlQueryModel * modal = new QSqlQueryModel(this);
    //query->prepare("SELECT * FROM people");
    //modal->setQuery(*query);
    // ui->tableView_2->setModel(modal);

    QSqlTableModel * model = new QSqlTableModel();
    model->setTable("people");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);


}


const QString MainWindow::PrintAllPersons()

{
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << name;
    }

}

bool MainWindow::dynamicQuery(QString & password)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT into people (password) VALUES (:password)");
    query.bindValue(":password", password);
    if(query.exec())
    {
        success = true;

    }
    else
    {
        qDebug() << "dynamicquery error:  " << query.lastError();
    }

    return success;
}

bool MainWindow::addPerson( QString  & name)
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


bool MainWindow::sendQuery(QString queryToDatabase)
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

bool MainWindow::sendRandomQuery()
{

    bool success=false;
    QString randomQuery;
    int lCol,lRow;
    if(ui->lineEdit->text()=="")
    {
        return false;

    }
    randomQuery=ui->lineEdit->text();
    QSqlQuery query(randomQuery);
    if(query.exec())
    {
        while(query.next())
        {
        qDebug() << "Wartosc query ";
        success = true;

        qDebug()<< "Query Success" << query.value(0).toString();
        }
    }
    else
    {
        qDebug()<< "Query failed" << query.lastError();
        success = false;
    }

    query = *new QSqlQuery(m_db);
    table_model = new QSqlQueryModel();
    QSqlQueryModel * modal = new QSqlQueryModel(this);
    query.prepare(randomQuery);
    modal->setQuery(query);
    ui->tableView_2->setModel(modal);
    return success;

}

void MainWindow::odswiezQueryModel()
{
    QSqlQuery query (m_db);
    query.prepare("???");
    query.exec();
    table_model->setQuery(query);
}

void MainWindow::on_przejdz_clicked()
{

    if (!sendRandomQuery())
    {
QMessageBox::warning(this, tr("Blad skladni"),
                     tr("Upewnij sie ze skladnia polecenia SQL jest poprawna"),
                     QMessageBox::Ok);
    }

    else {
        QMessageBox msg;
        QPushButton * otworzButton = msg.addButton(tr("Otworz"),QMessageBox::AcceptRole );
        QPushButton * abort = msg.addButton(tr("Zrezygnuj"),QMessageBox::RejectRole);

        msg.exec();

        if (msg.clickedButton() == otworzButton)
        {

            Dialog d("people");
            d.exec();
        }
        else if(msg.clickedButton() == abort)
        {
            return;
        }

    }


}
