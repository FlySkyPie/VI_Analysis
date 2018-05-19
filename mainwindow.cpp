#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <cstdlib>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1187,755);        //set windows size
    AppPath = QDir::currentPath();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), AppPath , tr("Experiment Data (*.txt)"));
    ui->lineEdit_9->setText(fileName);
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), AppPath, tr("Experiment Data (*.txt)"));
    ui->lineEdit_5->setText(fileName);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), AppPath, tr("Experiment Data (*.txt)"));
    ui->lineEdit_6->setText(fileName);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), AppPath, tr("Experiment Data (*.txt)"));
    ui->lineEdit_7->setText(fileName);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("選擇實驗數據"), AppPath, tr("Experiment Data (*.txt)"));
    ui->lineEdit_8->setText(fileName);
}

//start analysis
void MainWindow::on_pushButton_6_clicked()
{
    //load data of dark
    QString path = ui->lineEdit_9->text();
    Data.initialize( path );


    //load 1st data
    path = ui->lineEdit_5->text();
    Data.addCurrentData( path );
    //load 2nd data
    path = ui->lineEdit_6->text();
    Data.addCurrentData( path );

    //load 3rd data
    path = ui->lineEdit_7->text();
    Data.addCurrentData( path );

    //load 4th data
    path = ui->lineEdit_8->text();
    Data.addCurrentData( path );

    //Data.ckeckDataLength();       //DEBUG


}
