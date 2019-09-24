#include "mainwindownew.h"
#include "ui_mainwindownew.h"
#include <QMessageBox>
#include <dbcontroller.h>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSettings>
#include <QSqlError>

MainWindowNew::MainWindowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowNew)
{
    ui->setupUi(this);
    db_controller = new DbController(this);
    qDebug() << "Rejestr dbcontr - " << db_controller;

    connect(ui->pushButtonConnect,SIGNAL(clicked()), this, SLOT(connectToServerRequested()));

    connect(this, SIGNAL(connectToServer(QString, QString, QString)),db_controller, SLOT(connectToServerRequested(QString, QString, QString)));
    connect(this,SIGNAL(getTablesNames()),db_controller,SLOT(getTablesNamesRequested()));
    connect(this,SIGNAL(selectTable(QString)),db_controller, SLOT(selectTableRequested(QString)));
connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(showTableRequested()));
    // db_contro

    connect(db_controller, SIGNAL(serverConnected()),this,SLOT(serverConnected()));
    connect(db_controller, SIGNAL(tableSelected(QSqlQueryModel *)),this, SLOT(displayTable(QSqlQueryModel *)));
    connect(db_controller,SIGNAL(gotTablesNames(QStringList)),this, SLOT(fillTableNames(QStringList)));


}

MainWindowNew::~MainWindowNew()
{
    delete ui;
}


void MainWindowNew::connectToServerRequested()
{
    QString engine;
    if (ui->radio_sqlite->isChecked())
    {
        engine = "sqlite";
        qDebug() << "Wybrano sqlite";
    }
    else if (ui->radio_postgress->isChecked())
    {
        engine="postgress";
    }
    else
    {

        QMessageBox::information(this,
                                 "Wrong engine",
                                 "Please choose engine",
                                 QMessageBox::Ok);
        return;
    }

    QString server = ui->lineEditServer->text(),
            database = ui->lineEditDatabase->text();

    if(server == "")
    {
        QMessageBox::information(this,
                                 "Invalid Connection Data",
                                 "Insert server address to connect",
                                 QMessageBox::Ok);
        return;
    }


    if (database =="")
    {
        QMessageBox::information(this,
                                 "Invalid Connection data",
                                 "Insert database name to connect",
                                 QMessageBox::Ok);
        return;

    }
  //tutaj klawisz disabled // ui->pushButtonConnect->setEnabled(false);
    ui->statusbar->showMessage("Connecting..");
    qDebug() << "Emituje sygnal do connectToServer";
    emit connectToServer(engine,server,database);
}

void MainWindowNew::serverConnected()
{
    ui->statusbar->showMessage(tr("Polaczono z bazą"));
   //ui->pushButtonConnect->setDisabled(true);
    //tu moze byc zle
    //disconnect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    //connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(disconnect))
qDebug() << "emituje gettablenames";
    emit getTablesNames();

}

void MainWindowNew::on_pushButtonDisconnect_clicked()
{

}

void MainWindowNew::serverErrorWithConnection(QString message)
{
    QMessageBox::critical(this,
                          "Connection failed",
                          message, 
                          QMessageBox::Ok);


    ui->pushButtonConnect->setEnabled(true);

    ui->statusbar->showMessage("Connection failed", 3000);
}


void MainWindowNew:: displayTable(QSqlQueryModel * model)
{

    if (!model->lastError().isValid())
        ui->tableView_3->setModel(model);
    ui->pushButtonConnect->setDisabled(false);
}

void MainWindowNew::fillTableNames(QStringList list)
{
 qDebug() << "sprawdzam czy lista nie jest pusta";
 if(list.length() == 0)

    QMessageBox::warning(this,
                         "Tables",
                         "There are no tables to display in the database",
                         QMessageBox::Ok);


    else
    {
       ui->comboBox->addItems(list);
       ui->comboBox->setEnabled(true);
       ui->comboBox->setFocus();
    }

}

void MainWindowNew::showTableRequested()
{
 delete ui->tableView_3->model();
    QString tab = ui->comboBox->currentText();
    emit selectTable(tab);
}


