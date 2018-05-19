#include "linechart2d.h"

LineChart2D::LineChart2D()
{
    Initialized = false;
    MaxOfX = 0;
    MaxOfY = 0;
    MinOfX = 0;
    MinOfY = 0;
}

void LineChart2D::clearData()
{
    Initialized = false;
    MaxOfX = 0;
    MaxOfY = 0;
    MinOfX = 0;
    MinOfY = 0;

    DataOfXAxis.clear();
    DataOfYAxis.clear();
}

double LineChart2D::getMaxOfX()
{
    return MaxOfX;
}
double LineChart2D::getMaxOfY()
{
    return MaxOfY;
}
double LineChart2D::getMinOfX()
{
    return MinOfX;
}
double LineChart2D::getMinOfY()
{
    return MinOfY;
}

void LineChart2D::addData(double x, double y)
{
    if( !Initialized )
    {
        MinOfX = MaxOfX = x;
        MinOfY = MaxOfY = y;
        Initialized = true;
    }
    if( x < MinOfX )
        MinOfX = x;
    if( y < MinOfY )
        MinOfY = y;
    if( x > MaxOfX )
        MaxOfX = x;
    if( y > MaxOfY )
        MaxOfY = y;

    DataOfXAxis.push_back( x );
    DataOfYAxis.push_back( y );
}
void LineChart2D::injectView( QGraphicsView * OldView)
{
    Scene = new QGraphicsScene();
    View = new QGraphicsView( OldView->window() );

    View->move(OldView->x(), OldView->y());

    Width = OldView->width();
    Height = OldView->height();


    View->setFixedSize(Width,Height);
    View->setScene(Scene);

    //disable scroll
    View->setSceneRect(0, 0, Width,Height);
    View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //handle view pointer
    QGraphicsView *tempView = OldView;

    OldView = View;

    delete tempView;

}
void  LineChart2D::reDraw()
{
    //fill background to white
    Scene->clear();
    QPixmap pic(Width,Height);
    pic.fill( QColor(255,255,255));

    QPainter painter(&pic);
    painter.setPen(Qt::black);

    uint FrameWidth,FrameHeight,MaxElement,MaxTemperature;
    float StepWidth,StepHeight;
    FrameWidth = Width - 20;        //frame's width
    FrameHeight = Height - 20;      //frame's height
    MaxElement = Width;               //how many element(data) that want show
    MaxTemperature = 800;           //maximum value of y axis
    StepWidth = 1.0 * FrameWidth / MaxElement;          // (x/element) ratio
    StepHeight = 1.0 * FrameHeight / MaxTemperature;    // (y/temerature) ratio

    //prepare draw axis line
    /*
    painter.setPen(Qt::gray);
    uint DistantX,DistantY;
    DistantX = 60;//FrameWidth / 10;
    DistantY = 100;

    //draw vertical line
    uint v_lines = MaxElement / DistantX;
    for(uint i=1;i<v_lines;i++)
    {
        uint x,y1,y2;
        x = 10 + DistantX * i;
        y1 = Height - 10;
        y2 = Height - 10 - FrameHeight;
        painter.drawLine(x,y1,x,y2);
    }

    //draw horizontal line
    uint lines = MaxTemperature / DistantY;
    for(uint i=1; i<=lines ;i++)
    {
        uint x1,x2,y;
        x1 = 10 ;
        x2 = 10 + FrameWidth;
        y = Height - 10 -  DistantY * i * StepHeight;
        painter.drawLine(x1,y,x2,y);
    }
*/
    //draw frame
    painter.setPen(Qt::black);
    painter.drawRect(10,10, FrameWidth, FrameHeight);

    Scene->addPixmap( pic );
}
