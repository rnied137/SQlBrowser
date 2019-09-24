#ifndef DIALOG_H
#define DIALOG_H
#include <QSqlTableModel>
#include <QDialog>

namespace Ui {
class Dialog;
}

class MainWindow;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(const QString & tableName, QWidget *parent = nullptr);
    ~Dialog();
    QString sqlQuery;
private slots:
    void submit();
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    MainWindow * main_window;
    QPushButton * submitButton;
    QPushButton * revertButton;
    QPushButton * buttonBox;
    QSqlTableModel * model;
};

#endif // DIALOG_H
