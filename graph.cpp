#include "graph.h"
#include "ui_graph.h"

/*
 ##########################################################
 #####                                                #####
 #####  GUI Seiter zur Darstellung eines Liniengraps  #####
 #####                                                #####
 ##########################################################
 */

//------------Startup Funktion---------------
//Signals und Slots verbinden (Interrupt)
graph::graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graph)
{
    ui->setupUi(this);
    client = new network(this);
    if(client->error == true)
    {
        //this->setVisible(false);  // Fenster Schließen
    }
    line_graph  = new plot(ui->customPlot,this);
    connect(client,SIGNAL(readyPlot(QVector<double>,QVector<int>)), line_graph, SLOT(realtimeDataSlot(QVector<double>,QVector<int>))); //Wenn neue Werte vorhanden sind soll gezeichnet werden

    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int))); //Anpassung der Y-Achse wenn ein größerer Wert zu ploten ist
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange))); //Anpassung der X-Achse
}

graph::~graph()
{
    delete ui;
}

//Knopf zum Pausieren der Anzeige
void graph::on_pushButton_clicked()
{
    if(line_graph->pause == true)
        line_graph->pause = false;
    else
        line_graph->pause = true;
    //ui->lineEdit->setText(QString::number(plot->current_analog[2]));
}

//------------------------------------------------------------------------//
//----------------Knöpfe zum Aktivieren einzelner linien------------------//
void graph::on_c_analog_0_clicked()
{
    if(ui->c_analog_0->checkState())
        line_graph->set_port_status(0,1);
    else
        line_graph->set_port_status(0,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_1_clicked()
{
    if(ui->c_analog_1->checkState())
        line_graph->set_port_status(1,1);
    else
        line_graph->set_port_status(1,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_2_clicked()
{
    if(ui->c_analog_2->checkState())
        line_graph->set_port_status(2,1);
    else
        line_graph->set_port_status(2,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_3_clicked()
{
    if(ui->c_analog_3->checkState())
        line_graph->set_port_status(3,1);
    else
        line_graph->set_port_status(3,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_4_clicked()
{
    if(ui->c_analog_4->checkState())
        line_graph->set_port_status(4,1);
    else
        line_graph->set_port_status(4,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_5_clicked()
{
    if(ui->c_analog_5->checkState())
        line_graph->set_port_status(5,1);
    else
        line_graph->set_port_status(5,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_6_clicked()
{
    if(ui->c_analog_6->checkState())
        line_graph->set_port_status(6,1);
    else
        line_graph->set_port_status(6,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_analog_7_clicked()
{
    if(ui->c_analog_7->checkState())
        line_graph->set_port_status(7,1);
    else
        line_graph->set_port_status(7,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}


void graph::on_c_digital_0_clicked()
{
    if(ui->c_digital_0->checkState())
        line_graph->set_port_status(8,1);
    else
        line_graph->set_port_status(8,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_1_clicked()
{
    if(ui->c_digital_1->checkState())
        line_graph->set_port_status(9,1);
    else
        line_graph->set_port_status(9,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_2_clicked()
{
    if(ui->c_digital_2->checkState())
        line_graph->set_port_status(10,1);
    else
        line_graph->set_port_status(10,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_3_clicked()
{
    if(ui->c_digital_3->checkState())
        line_graph->set_port_status(11,1);
    else
        line_graph->set_port_status(11,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_4_clicked()
{
    if(ui->c_digital_4->checkState())
        line_graph->set_port_status(12,1);
    else
        line_graph->set_port_status(12,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_5_clicked()
{
    if(ui->c_digital_5->checkState())
        line_graph->set_port_status(13,1);
    else
        line_graph->set_port_status(13,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_6_clicked()
{
    if(ui->c_digital_6->checkState())
        line_graph->set_port_status(14,1);
    else
        line_graph->set_port_status(14,0);
    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}
void graph::on_c_digital_7_clicked()
{
    if(ui->c_digital_7->checkState())
        line_graph->set_port_status(15,1);
    else
        line_graph->set_port_status(15,0);

    client->send_settings(line_graph->port_status);
    line_graph->plot_settings();
}

//--------------Skalierung der X-Achse-------------------//
void graph::xAxisChanged(QCPRange range)
{
  ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

//--------------Skalierung der Y-Achse-------------------//
void graph::horzScrollBarChanged(int value)
{
  if (qAbs(ui->customPlot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    ui->customPlot->xAxis->setRange(value/100.0, ui->customPlot->xAxis->range().size(), Qt::AlignCenter);
    ui->customPlot->replot();
  }
}

