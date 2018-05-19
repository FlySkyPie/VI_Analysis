#include "dataanalyzer.h"

#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>

#include <sstream>
#include <iostream>

using namespace std;

DataAnalyzer::DataAnalyzer()
{

}

/* @todo initialize Data Anolyzer by string of data path
 * @param QString FilePath
 */
void DataAnalyzer::initialize( QString FilePath )
{
    QFile file( FilePath );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while ( !in.atEnd() )
    {
        QString line = in.readLine();

        if( line=="" )
            continue;

        //cout << line.toUtf8().constData() <<endl;     //DEBUG

        QStringList data = line.split('	');     //this is ascii 0x09

        istringstream sv( data.at(0).toUtf8().constData() );
        double voltage;
        sv >> voltage;

        istringstream si( data.at(1).toUtf8().constData() );
        double current;
        si >> current;


        addFirstVoltageData( voltage );
        addFirstCurrentData( current );
    }
}



void DataAnalyzer::addFirstVoltageData( double voltage )
{
    FirstVoltage.push_back( voltage );
}
void DataAnalyzer::addFirstCurrentData( double current )
{
    FirstCurrent.push_back( current );
}

/*
 * @
 */
void DataAnalyzer::addCurrentData( QString FilePath )
{
    QFile file( FilePath );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //create a vector
    vector <double> Current;


    QTextStream in(&file);
    while ( !in.atEnd() )
    {
        QString line = in.readLine();

        if( line=="" )
            continue;

        QStringList data = line.split('	');     //this is ascii 0x09

        istringstream si( data.at(1).toUtf8().constData() );
        double current;
        si >> current;

        Current.push_back( current );
    }

    CurrentDatas.push_back( Current );

}

/*
 * @todo ckeck how many data that the object had.
 */
void DataAnalyzer::ckeckDataLength()
{
    //check first data
     cout << "No.0"  << " " << FirstVoltage.size() << endl;

    for (int i=0; i<CurrentDatas.size();i++ )
    {
        int size = CurrentDatas.at(i).size();
        cout << "No." << i+1 << " " << size << endl;
    }


}

DataAnalyzer::~DataAnalyzer()
{

}
