#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include "network.h"
#include "plot.h"

/*
 ##########################################################
 #####                                                #####
 #####  GUI Seiter zur Darstellung eines Liniengraps  #####
 #####                                                #####
 ##########################################################
 */

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = 0);
    ~graph();

private slots:
    void on_pushButton_clicked();

    void on_c_analog_0_clicked();
    void on_c_analog_1_clicked();
    void on_c_analog_2_clicked();
    void on_c_analog_3_clicked();
    void on_c_analog_4_clicked();
    void on_c_analog_5_clicked();
    void on_c_analog_6_clicked();
    void on_c_analog_7_clicked();

    void on_c_digital_0_clicked();
    void on_c_digital_1_clicked();
    void on_c_digital_2_clicked();
    void on_c_digital_3_clicked();
    void on_c_digital_4_clicked();
    void on_c_digital_5_clicked();
    void on_c_digital_6_clicked();
    void on_c_digital_7_clicked();

    void horzScrollBarChanged(int);
    void xAxisChanged(QCPRange);

private:
    Ui::graph *ui;
    network * client;
    plot * line_graph;
};

#endif // GRAPH_H
