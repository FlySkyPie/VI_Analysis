#ifndef LINECHART3D_H
#define LINECHART3D_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include <iostream>
#include <vector>

using namespace std;

class LineChart3D
{
public:
    LineChart3D();

    QGraphicsScene *Scene;
    QGraphicsView *View;

    uint Width;
    uint Height;

    double MaxOfX;
    double MaxOfY;
    double MaxOfZ;
    double MinOfX;
    double MinOfY;
    double MinOfZ;

    bool Initialized;

    float RateOfX;
    float RateOfY;
    float RateOfZ;

    vector<double> DataOfXAxis;
    vector<double> DataOfYAxis;
    vector<double> DataOfZAxis;

    void injectView( QGraphicsView * OldView);

    void addData(double, double, double);
};

#endif // LINECHART3D_H
