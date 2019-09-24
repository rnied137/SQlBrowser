#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(const QString & tableName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
        model = new QSqlTableModel(this);
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("First name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

        //ui->tableWidget->
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{


}


void Dialog::submit()
{

}
