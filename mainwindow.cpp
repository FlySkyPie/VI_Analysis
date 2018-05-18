#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     this->setFixedSize(1187,755);        //set windows size
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), "/home", tr("Experiment Data (*.csv)"));
    ui->lineEdit_9->setText(fileName);
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), "/home", tr("Experiment Data (*.csv)"));
    ui->lineEdit_5->setText(fileName);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), "/home", tr("Experiment Data (*.csv)"));
    ui->lineEdit_6->setText(fileName);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), "/home", tr("Experiment Data (*.csv)"));
    ui->lineEdit_7->setText(fileName);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), "/home", tr("Experiment Data (*.csv)"));
    ui->lineEdit_8->setText(fileName);
}

//start analysis
void MainWindow::on_pushButton_6_clicked()
{
    QString path = ui->lineEdit_9->text();

}
