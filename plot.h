#ifndef PLOT_H
#define PLOT_H

#include <QtCore>
#include <QVector>
#include <QObject>
#include <qcustomplot.h>

/*
 ##########################################################
 #####                                                #####
 #####   Funktion zur Darstellung des Liniengraps     #####
 #####                                                #####
 ##########################################################
 */

class plot : public QObject
{
    Q_OBJECT
public:
    explicit plot(QCustomPlot *, QObject *parent = 0);
    void init();
    void set_port_status(int,int);

    int port_status[16];
    void plot_settings();
    bool pause = false;

private:
    QTimer *dataTimer; //= new QTimer(this);
    bool complete_graph; 
    int rgb[16][3];
    QVector<int> line_counter;
    QCustomPlot *cplot;

    void checkBoxes();


public slots:
    void realtimeDataSlot(QVector<double>,QVector<int>);

};

#endif // PLOT_H
