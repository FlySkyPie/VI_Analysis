#include "linechart3d.h"

LineChart3D::LineChart3D()
{
    // (px/data value)

    Initialized = false;
}

void LineChart3D::injectView( QGraphicsView * OldView)
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

void LineChart3D::addData( double x, double y, double z )
{
    if( !Initialized )
    {
        MinOfX = MaxOfX = x;
        MinOfY = MaxOfY = y;
        MinOfZ = MaxOfZ = z;
        Initialized = true;
    }
    if( x < MinOfX )
        MinOfX = x;
    if( y < MinOfY )
        MinOfY = y;
    if( z < MinOfZ )
        MinOfZ = z;
    if( x > MaxOfX )
        MaxOfX = x;
    if( y > MaxOfY )
        MaxOfY = y;
    if( z > MaxOfZ )
        MaxOfZ = z;

    DataOfXAxis.push_back( x );
    DataOfYAxis.push_back( y );
    DataOfZAxis.push_back( z );
}
