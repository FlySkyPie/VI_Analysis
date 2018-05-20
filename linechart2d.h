#ifndef LINECHART2D_H
#define LINECHART2D_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include <iostream>
#include <vector>

using namespace std;
class LineChart2D
{
public:
    LineChart2D();

    void injectView( QGraphicsView * );

    void reDraw();
    void clearData();
    void LinearRegression();
    void addData(double, double);

    double getMaxOfX();
    double getMaxOfY();
    double getMinOfX();
    double getMinOfY();
    double getSlope();

private:
    uint Width;
    uint Height;

    double MaxOfX;
    double MaxOfY;
    double MinOfX;
    double MinOfY;

    bool Initialized;

    QGraphicsScene *Scene;
    QGraphicsView *View;

    vector<double> DataOfXAxis;
    vector<double> DataOfYAxis;

    double a;
    double b;

};

#endif // LINECHART2D_H
