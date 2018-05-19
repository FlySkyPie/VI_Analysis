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

    void addData(double, double);

    double getMaxOfX();
    double getMaxOfY();
    double getMinOfX();
    double getMinOfY();

    void clearData();


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

};

#endif // LINECHART2D_H
