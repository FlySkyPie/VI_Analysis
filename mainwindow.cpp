#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1187,755);        //set windows size
    AppPath = QDir::currentPath();

    Chart.injectView( ui->graphicsView );
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
    double power = 0;
    //load data of dark
    QString path = ui->lineEdit_9->text();
    Data.initialize( path );


    //load 1st data
    path = ui->lineEdit_5->text();
    power = ui->lineEdit->text().toDouble();
    Data.addCurrentData( power, path );
    //load 2nd data
    path = ui->lineEdit_6->text();
    power = ui->lineEdit_2->text().toDouble();
    Data.addCurrentData( power, path );

    //load 3rd data
    path = ui->lineEdit_7->text();
    power = ui->lineEdit_3->text().toDouble();
    Data.addCurrentData( power, path );

    //load 4th data
    path = ui->lineEdit_8->text();
    power = ui->lineEdit_4->text().toDouble();
    Data.addCurrentData( power, path );

    //Data.ckeckDataLength();       //DEBUG
    //set maxium of scroll bar
    ui->horizontalSlider->setMaximum( Data.getLength() - 1 );

}

void MainWindow::redrawSlice(uint index)
{
    //load new data
    Chart.clearData();
    vector <double>P = Data.getPowers();
    vector <double>DI = Data.getDeltaCurrents( index );

    cout << "new data\n";

    for(uint i=0; i< P.size();i++)
    {
        Chart.addData( P[i], DI[i] );
        cout << i << ":" << P[i] << "," << DI[i] << endl;
    }

    //cout << Chart.getMinOfX() <<  "~" << Chart.getMaxOfX() << "," << Chart.getMinOfY() << "~" << Chart.getMaxOfY() << endl;

    //redraw chart
    Chart.reDraw();


}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QString str = "Voltage = "  + QString::number( value )  +" Volt";
    ui->label_11->setText( str );

    redrawSlice( abs(value) );
}
