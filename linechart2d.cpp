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
    QBrush currentBrush = painter.brush();

    uint FrameWidth,FrameHeight, Boundary;
    Boundary = 10;
    double StepWidth,StepHeight;
    FrameWidth = Width - Boundary*2;        //frame's width
    FrameHeight = Height - Boundary*2;      //frame's height

    StepWidth = 1.0 * FrameWidth / (MaxOfX - MinOfX);          // (px/data unit) ratio
    StepHeight = 1.0 * FrameHeight / (MaxOfY - MinOfY);    // (px/data unit) ratio


    //draw vertical and horizontal
    painter.setPen(Qt::gray);
    painter.drawLine(Boundary, (Height - Boundary)/2 , Width - Boundary, (Height - Boundary)/2);
    painter.drawLine((Width - Boundary)/2, Boundary, (Width - Boundary)/2, Height - Boundary);

    /*
     * @todo Linear regression線性回歸
     * @link https://blog.csdn.net/qll125596718/article/details/8248249
     */
    double t1=0, t2=0, t3=0, t4=0,a,b;
    for(uint i=0; i<DataOfXAxis.size(); ++i)
    {
        double x,y;
        x = DataOfXAxis.at(i);
        y = DataOfYAxis.at(i);
        t1 += x*x;
        t2 += x;
        t3 += x*y;
        t4 += y;
    }
    a = (t3*DataOfXAxis.size() - t2*t4) / (t1*DataOfXAxis.size() - t2*t2);
    b = (t1*t4 - t2*t3) / (t1 * DataOfXAxis.size() - t2*t2);


    //draw data
    QBrush brush(Qt::blue);
    painter.setBrush(brush);
    for(uint i =0; i<DataOfXAxis.size(); i++ )
    {
        uint x,y;
        x = Boundary + (DataOfXAxis.at(i) - MinOfX) * StepWidth;
        y = Boundary + FrameHeight - (DataOfYAxis.at(i) - MinOfY) * StepHeight;
        painter.drawEllipse(QPointF(x,y), 3, 3);
        QString str = "(" + QString::number(DataOfXAxis.at(i)) + "," + QString::number(DataOfYAxis.at(i)) + ")";
        painter.drawText( QPoint(x,y), str );
    }

    //draw line
    painter.setPen(Qt::black);

    double Lx1,Ly1,Lx2,Ly2;

    Lx1 = MinOfX;
    Ly1 = a * MinOfX +b;

    Lx2 = MaxOfX;
    Ly2 = a * MaxOfX +b;

    uint Px1,Py1,Px2,Py2;

    Px1 = Boundary + (Lx1 - MinOfX) * StepWidth;
    Py1 = Boundary + FrameHeight - (Ly1 - MinOfY) * StepHeight;
    Px2 = Boundary + (Lx2 - MinOfX) * StepWidth;
    Py2 = Boundary + FrameHeight - (Ly2 - MinOfY) * StepHeight;

    painter.drawLine( Px1, Py1, Px2, Py2);

    //draw frame
    painter.setBrush(currentBrush);
    painter.setPen(Qt::black);
    painter.drawRect(10,10, FrameWidth, FrameHeight);

    Scene->addPixmap( pic );
}

/*
 * @todo Linear regression線性回歸
 * @link https://blog.csdn.net/qll125596718/article/details/8248249
 */
void LineChart2D::LinearRegression()
{
    double t1=0, t2=0, t3=0, t4=0;
    for(uint i=0; i<DataOfXAxis.size(); ++i)
    {
        double x,y;
        x = DataOfXAxis.at(i);
        y = DataOfYAxis.at(i);
        t1 += x*x;
        t2 += x;
        t3 += x*y;
        t4 += y;
    }
    a = (t3*DataOfXAxis.size() - t2*t4) / (t1*DataOfXAxis.size() - t2*t2);
    b = (t1*t4 - t2*t3) / (t1 * DataOfXAxis.size() - t2*t2);
}


double LineChart2D::getSlope()
{
    return a;
}
