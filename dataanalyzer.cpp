#include "dataanalyzer.h"

#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>

#include <sstream>

DataAnalyzer::DataAnalyzer()
{

}

//initialize Data Anolyzer by string of data path
void DataAnalyzer::initialize( QString str )
{
    QFile file( str );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while ( !in.atEnd() )
    {
        QString line = in.readLine();

        QStringList data = line.split(' ');

        istringstream sv( data.at(0).toUtf8().constData() );
        double voltage;
        sv >> voltage;

        istringstream si( data.at(1).toUtf8().constData() );
        double current;
        si >> current;


        addFirstVoltageData( voltage );
        addFirstCurrentData( current );

        process_line(line);
    }

}

void DataAnalyzer::addFirstVoltageData( double voltage )
{



}
void DataAnalyzer::addFirstCurrentData( double current )
{

}
DataAnalyzer::~DataAnalyzer()
{

}
