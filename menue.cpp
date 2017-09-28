#include "menue.h"
#include "ui_menue.h"
#include "config.h"
#include "database.h"
#include "messdaten.h"
#include "graph.h"

/*
 ##########################################################
 #####                                                #####
 #####        Menü zur Auswahl der Funktion           #####
 #####                                                #####
 ##########################################################
 */

menue::menue(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menue)
{
    ui->setupUi(this);
}

menue::~menue()
{
    delete ui;
}

//----------Öffnet das GUI um Konfigurationen zu erstellen----------//
void menue::on_men_button_config_clicked()
{
    database db;
    db.connect();
    config conf;
    conf.exec();
}

//----------Öffnet das GUI um Messwerte anzuzeigen und zu verwalten----------//
void menue::on_men_button_data_clicked()
{
    Messdaten val;
    val.exec();
}

//----------Öffnet das GUI zur Anzeige eines Echtzeit Liniengraphens----------//
void menue::on_men_button_realtime_clicked()
{
    graph graph;
    graph.exec();
}
