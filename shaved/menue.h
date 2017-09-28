#ifndef MENUE_H
#define MENUE_H

#include <QMainWindow>

/*
 ##########################################################
 #####                                                #####
 #####        Menü zur Auswahl der Funktion           #####
 #####                                                #####
 ##########################################################
 */

namespace Ui {
class menue;
}

class menue : public QMainWindow
{
    Q_OBJECT

public:
    explicit menue(QWidget *parent = 0);
    ~menue();

private slots:
    void on_men_button_config_clicked();    //Öffnet das GUI um Konfigurationen zu erstellen

    void on_men_button_data_clicked();      //Öffnet das GUI um Messwerte anzuzeigen und zu verwalten

    void on_men_button_realtime_clicked();  //Öffnet das GUI zur Anzeige eines Echtzeit Liniengraphens

private:
    Ui::menue *ui;
};

#endif // MENUE_H
