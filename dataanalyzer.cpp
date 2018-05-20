#include "dataanalyzer.h"



DataAnalyzer::DataAnalyzer()
{

}

vector <double>DataAnalyzer::getDeltaCurrents( uint index)
{
    uint amount = PowerDatas.size();
    vector <double> datas;

    for(uint i =0;i<amount;i++)
    {
        datas.push_back( CurrentDatas.at(i).at(index) );
    }
    return datas;
}

vector <double>DataAnalyzer::getPowers()
{
    uint amount = PowerDatas.size();
    vector <double> datas;

    for(uint i =0;i<amount;i++)
    {
        datas.push_back( PowerDatas.at(i) );
    }
    return datas;
}

/* @todo initialize Data Anolyzer by string of data path
 * @param QString FilePath
 */
void DataAnalyzer::initialize( QString FilePath )
{
    QFile file( FilePath );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while ( !in.atEnd() )
    {
        QString line = in.readLine();

        if( line=="" )
            continue;

        QStringList data = line.split('	');     //this is ascii 0x09

        //trans Qstring to double
        istringstream sv( data.at(0).toUtf8().constData() );
        double voltage;
        sv >> voltage;

        //trans Qstring to double
        istringstream si( data.at(1).toUtf8().constData() );
        double current;
        si >> current;


        addFirstVoltageData( voltage );
        addFirstCurrentData( current );
    }
}



void DataAnalyzer::addFirstVoltageData( double voltage )
{
    FirstVoltage.push_back( voltage );
}
void DataAnalyzer::addFirstCurrentData( double current )
{
    FirstCurrent.push_back( current );
}

/* @todo add current datas by string of data path
 * @param Double _Power
 * @param QString FilePath
 */
void DataAnalyzer::addCurrentData( double _Power ,QString FilePath )
{
    QFile file( FilePath );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //create a vector
    vector <double> Current;


    QTextStream in(&file);
    while ( !in.atEnd() )
    {
        QString line = in.readLine();

        if( line=="" )
            continue;

        QStringList data = line.split('	');     //this is ascii 0x09

        istringstream si( data.at(1).toUtf8().constData() );
        double current;
        si >> current;

        double DeltaOfCurrent = current - FirstCurrent.at( Current.size() );
        double v = FirstVoltage.at( Current.size() );
        Chart3D->addData( v, _Power, DeltaOfCurrent  );

        Current.push_back( DeltaOfCurrent );
    }

    CurrentDatas.push_back( Current );  //add data serial
    PowerDatas.push_back(_Power);
}

/*
 * @todo ckeck how many data that the object had.
 * @ignore be used to DEBUG
 */
void DataAnalyzer::ckeckDataLength()
{
    //check first data
     cout << "No.0"  << " " << FirstVoltage.size() << endl;

    for (uint i=0; i<CurrentDatas.size();i++ )
    {
        int size = CurrentDatas.at(i).size();
        cout << "No." << i+1 << " " << size << endl;
    }
}

uint DataAnalyzer::getLength()
{
    return FirstVoltage.size();
}

DataAnalyzer::~DataAnalyzer()
{

}

double DataAnalyzer::getVoltage(uint index)
{
    return FirstVoltage.at(index);
}

void DataAnalyzer::draw3DChart()
{
    double RateOfVI = (Chart3D->MaxOfX - Chart3D->MinOfX) / ( Chart3D->MaxOfZ - Chart3D->MinOfZ ) * 0.5;

    double MaxOfPx,MaxOfPy,MinOfPx, MinOfPy;

    //get maxium and minium of 2 deimension double system
    for(int i=0; i< Chart3D->DataOfXAxis.size() ;i++)
    {
        double x = Chart3D->DataOfXAxis.at(i)
               ,y = Chart3D->DataOfYAxis.at(i)
               ,z = Chart3D->DataOfZAxis.at(i);

        double Px,Py;

        Px = 0.707 * x +  0.866 * y;
        Py = -0.707 * x + 0.5 * y + 1 * z * RateOfVI;

        if( i==0 )
        {
            MaxOfPx = MinOfPx = Px;
            MaxOfPy = MinOfPy = Py;
        }
        if( Px > MaxOfPx )
            MaxOfPx = Px;
        if( Py > MaxOfPy )
            MaxOfPy = Py;
        if( Px < MinOfPx )
            MinOfPx = Px;
        if( Py < MinOfPy )
            MinOfPy = Py;

    }

    //create 3d frame
    double x[2],y[2],z[2],FPx[2][2][2],FPy[2][2][2];
    x[0] = Chart3D->MinOfX;
    y[0] = Chart3D->MinOfY;
    z[0] = Chart3D->MinOfZ;
    x[1] = Chart3D->MaxOfX;
    y[1] = Chart3D->MaxOfY;
    z[1] = Chart3D->MaxOfZ;


    for( uint i = 0; i<2; i++ ) //x
        for( uint j=0; j<2; j++ )   //y
            for( uint k=0; k<2; k++)    //z
            {
                double Px,Py;
                FPx[i][j][k] = Px = 0.707 * x[i] +  0.866 * y[j];
                FPy[i][j][k] = Py = -0.707 * x[i] + 0.5 * y[j] + 1 * z[k] * RateOfVI;

                if( Px > MaxOfPx )
                    MaxOfPx = Px;
                if( Py > MaxOfPy )
                    MaxOfPy = Py;
                if( Px < MinOfPx )
                    MinOfPx = Px;
                if( Py < MinOfPy )
                    MinOfPy = Py;
            }


    double Width = Chart3D->Width
           ,Height = Chart3D->Height;

    //rate of px/floatX in 2 Dimensions system
    double RateOfX = 1.0 * Width / (MaxOfPx - MinOfPx );
    double RateOfY = 1.0 * Height / (MaxOfPy - MinOfPy );

    //fill background to white
    QGraphicsScene *Scene = Chart3D->Scene;
    Scene->clear();
    QPixmap pic(Width,Height);
    pic.fill( QColor(255,255,255));

    QPainter painter(&pic);
    painter.setPen(Qt::black);
    QBrush currentBrush = painter.brush();

    //start to draw line
    srand(std::time(nullptr));
    uint R=0,G=0,B=0,C;
    C = rand() % 6 + 1;
    for( uint j=0; j<PowerDatas.size();j++ )
    {
        //generate color
        while(1)
        {
            R = (C%2)?   rand() % 50 : ( 200 + rand()%55 );
            G = ( C/2%2 ) ?  rand() % 50 : ( 200 + rand()%55 );
            B = ( C/4%2 ) ?  rand() % 50 : ( 200 + rand()%55 );
            double Brightness = 0.299*R + 0.587*G + 0.114*B;
            if(Brightness>55)
                break;
        }
        C = (C==6) ? 1 : C+1; //C = (C + (rand() %3) ) %6 +1;

        painter.setPen(QColor( R, G, B ));
        double power = PowerDatas.at(j);
        double volt;
        double Dcurrent ;
        for( uint i=0;i<FirstVoltage.size() ;i++)
        {
            if( i == 0)
            {
                volt = FirstVoltage.at(i);
                Dcurrent = CurrentDatas.at( j ).at( i );
            }

            double NewVolt = FirstVoltage.at(i);
            double NewDcurrent = CurrentDatas.at( j ).at( i );

            double Px1,Py1,Px2,Py2;

            Px1 =  0.707 * volt + 0.866 * power;
            Py1 = -0.707 * volt + 0.5 * power + 1 * Dcurrent*RateOfVI;

            Px2 = 0.707 * NewVolt + 0.866 * power;
            Py2 = -0.707 * NewVolt + 0.5 * power + 1 * NewDcurrent*RateOfVI;

            volt = NewVolt;
            Dcurrent = NewDcurrent;

            Px1 = (Px1 - MinOfPx) * RateOfX;
            Py1 = (Py1 - MinOfPy) * RateOfY;
            Px2 = (Px2 - MinOfPx) * RateOfX;
            Py2 = (Py2 - MinOfPy) * RateOfY;

            painter.drawLine( Px1, Height - Py1, Px2, Height -  Py2 );
        }
    }
    //draw frame
    painter.setPen(Qt::gray);
    for( uint i = 0; i<2; i++ ) //x
        for( uint j=0; j<2; j++ )   //y
            for( uint k=0; k<2; k++)    //z
            {
                FPx[i][j][k] =  (FPx[i][j][k] - MinOfPx) * RateOfX;
                FPy[i][j][k] =  Height - (FPy[i][j][k] - MinOfPy) * RateOfY;
            }

    //draw x vecotr
    for( uint j=0; j<2; j++ )
        for( uint k=0; k<2; k++)
            painter.drawLine( FPx[0][j][k], FPy[0][j][k], FPx[1][j][k], FPy[1][j][k] );

    //draw y vector
    for( uint j=0; j<2; j++ )
        for( uint k=0; k<2; k++)
            painter.drawLine( FPx[j][0][k], FPy[j][0][k], FPx[j][1][k], FPy[j][1][k] );

    //draw z vector
    for( uint j=0; j<2; j++ )
        for( uint k=0; k<2; k++)
            painter.drawLine( FPx[j][k][0], FPy[j][k][0], FPx[j][k][1], FPy[j][k][1] );

    Scene->addPixmap( pic );
}

double *DataAnalyzer::getMaxSlope()
{
    double *max = new double[2];
    for(uint j=0; j<FirstVoltage.size();j++ )
    {
        //Linear regression
        double t1=0, t2=0, t3=0, t4=0,a,b;
        for(uint i=0; i<PowerDatas.size(); ++i)
        {
            double x,y;
            x = PowerDatas.at(i);
            y = CurrentDatas.at(i).at(j);
            t1 += x*x;
            t2 += x;
            t3 += x*y;
            t4 += y;
        }
        a = (t3*PowerDatas.size() - t2*t4) / (t1*PowerDatas.size() - t2*t2);
        b = (t1*t4 - t2*t3) / (t1 * PowerDatas.size() - t2*t2);

        if( abs(a)> max[1] )
        {
            max[0] = FirstVoltage.at(j);
            max[1] = abs(a);
        }
    }
    return max;
}
