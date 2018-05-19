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

    void initialize( QString );
    void addFirstVoltageData( double );
    void addFirstCurrentData( double );
    void addCurrentData( double, QString str );
    void ckeckDataLength();
    uint getLength();

    vector <double> getDeltaCurrents( uint index);
    vector <double> getPowers();

    double getVoltage(uint index);

    LineChart3D * Chart3D;

    void draw3DChart();

    double *getMaxSlope();


private:
    vector <double> FirstVoltage;
    vector <double> FirstCurrent;
    vector <vector <double> > CurrentDatas;
    vector <double> PowerDatas;

};

#endif // DATAANALYZER_H
