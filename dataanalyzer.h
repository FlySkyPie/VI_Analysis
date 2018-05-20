#ifndef DATAANALYZER_H
#define DATAANALYZER_H

#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>

#include <vector>
#include <cstring>
#include <array>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "linechart3d.h"

using namespace std;

class DataAnalyzer
{
public:
    DataAnalyzer();
    ~DataAnalyzer();


    LineChart3D * Chart3D;

    void initialize( QString );
    void addFirstVoltageData( double );
    void addFirstCurrentData( double );
    void addCurrentData( double, QString str );
    void ckeckDataLength();
    void draw3DChart();

    uint getLength();
    double getVoltage(uint index);
    double *getMaxSlope();
    vector <double> getDeltaCurrents( uint index);
    vector <double> getPowers();

private:
    vector <double> FirstVoltage;
    vector <double> FirstCurrent;
    vector <vector <double> > CurrentDatas;
    vector <double> PowerDatas;
};

#endif // DATAANALYZER_H
