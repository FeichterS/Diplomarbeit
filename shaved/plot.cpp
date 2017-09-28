#include "plot.h"

/*
 ##########################################################
 #####                                                #####
 #####   Funktion zur Darstellung des Liniengraps     #####
 #####                                                #####
 ##########################################################
 */

//------------------Startup Funktion---------------------------//
plot::plot(QCustomPlot *plot,QObject *parent) : QObject(parent)
{
    cplot = plot;
    for(int i=0; i < 16; i++)
    {
        port_status[i] = 0; //Alle Linien ausblenden
    }
    //Farbcodes definieren
    rgb[0][0] = 255;
    rgb[0][1] = 0;
    rgb[0][2] = 0;

    rgb[1][0] = 255;
    rgb[1][1] = 255;
    rgb[1][2] = 0;

    rgb[2][0] = 255;
    rgb[2][1] = 0;
    rgb[2][2] = 255;

    rgb[3][0] = 0;
    rgb[3][1] = 255;
    rgb[3][2] = 0;

    rgb[4][0] = 0;
    rgb[4][1] = 255;
    rgb[4][2] = 255;

    rgb[5][0] = 0;
    rgb[5][1] = 0;
    rgb[5][2] = 255;

    rgb[6][0] = 0;
    rgb[6][1] = 0;
    rgb[6][2] = 0;

    rgb[7][0] = 100;
    rgb[7][1] = 100;
    rgb[7][2] = 100;

    for(int i = 0; i < 8; i++) //Analoggraphen erstellen
    {
        cplot->addGraph();
        cplot->graph(i)->setPen(QPen(QColor(rgb[i][0],rgb[i][1],rgb[i][2])));
        cplot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        cplot->graph(i)->setLineStyle(QCPGraph::lsLine);
    }
    for(int i = 0; i < 8; i++) //Digitalgraphen erstellen
    {
        cplot->addGraph();
        cplot->graph(i+8)->setPen(QPen(QColor(rgb[i][0],rgb[i][1],rgb[i][2])));
        cplot->graph(i+8)->setLineStyle(QCPGraph::lsStepRight);
        cplot->graph(i+8)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 5));
    }
}

void plot::set_port_status(int port,int stat)
{
    port_status[port] = stat;
}

//-------------Funktion zum Aktualisieren des Plots------------------------------------//
//Alle Datenpunkte werden in einen Vector gespeichert, über addData(x,y) lässt sich ein neuer
//Datenpunkt erstellen
void plot::realtimeDataSlot(QVector<double> current_analog,QVector<int> current_digital)
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // Vergangene Zeit in Sekunden
    static double lastPointKey = 0;


    if (key-lastPointKey > 0.002) // Höchstens alle 2ms einen neuen Wert einfügen
    {

        for(int i = 0; i < 16;i++)
        {
            if(i < 8)
            {
                cplot->graph(i)->addData(key,current_analog[i]);    //Analogwerte hinzufügen
            }
            else
               cplot->graph(i)->addData(key,current_digital[i-8]);  //DIgitalwerte hinzufügen
        }
      lastPointKey = key;
    }
    if(pause == false) //Nur Reploten wenn nicht pausiert ist, wenn pausiert ist werden die Werte weiter hinzugefügt, aber nicht angezeigt
    {
        cplot->xAxis->setRange(key, 8, Qt::AlignRight);
        cplot->replot();
    }
}

//Einstellungen des Plots
//Ob Einzelne graphen sichtbar sind
void plot::plot_settings()
{
    for(int i = 0; i < 16; i++)
    {
        if(port_status[i] != 1)
            cplot->graph(i)->setVisible(false);
        else
            cplot->graph(i)->setVisible(true);
    }


    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);    //Zeitformat
    timeTicker->setTimeFormat("%h:%m:%s");
    cplot->xAxis->setTicker(timeTicker);                                    //X-Achse mit Zeit verknüpfen
    cplot->axisRect()->setupFullAxesBox();
    cplot->yAxis->setRange(0, 20);                                          //Y-Achse festlegen

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(cplot->xAxis, SIGNAL(rangeChanged(QCPRange)), cplot->xAxis2, SLOT(setRange(QCPRange)));
    connect(cplot->yAxis, SIGNAL(rangeChanged(QCPRange)), cplot->yAxis2, SLOT(setRange(QCPRange)));
    qDebug()<< "Settings";
}
