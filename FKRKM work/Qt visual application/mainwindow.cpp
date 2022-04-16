#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <workers.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workrs(new std::list<workers>)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete workrs;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString surname = ui->surname->text();
    QString hours_worked = ui->hours_worked->text();
    QString hourly_traffic = ui->hourly_traffic->text();
    QString number_dependents = ui->number_dependents->text();

    workrs->push_back(workers(surname, hours_worked.toInt(), hourly_traffic.toInt(), number_dependents.toInt()));

    ui->textEdit->append(workrs->back().toString());

    ui ->surname->setText("");
    ui ->hours_worked->setText("");
    ui ->hourly_traffic->setText("");
    ui ->number_dependents->setText("");

    QMessageBox::StandardButton reply = QMessageBox::question(this, "", "Продовжити?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::No)
    {
        double max = workrs->front().get_salary();
        for(auto i: *workrs)
        {
            if(i.get_salary() > max)
            {
                max = i.get_salary();
            }
        }
        QMessageBox::about(this, "МАКСИМАЛЬНА ЗАРОБІТНА ПЛАТА", "Максимальна заробітна плата: " + QString::number(max));
        QApplication::quit();
    }

}

