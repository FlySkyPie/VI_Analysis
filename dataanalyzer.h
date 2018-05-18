#ifndef DATAANALYZER_H
#define DATAANALYZER_H

#include <vector>
#include <cstring>

#include <QString>

using namespace std;

class DataAnalyzer
{
public:
    DataAnalyzer();
    ~DataAnalyzer();

    void initialize( QString );
    void addFirstVoltageData( double );
    void addFirstCurrentData( double );

private:
    vector <double> FirstVoltage;
    vector <double> FirstCurrent;
    vector <vector <double> > Current;

};

#endif // DATAANALYZER_H
