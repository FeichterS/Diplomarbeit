#include "config.h"
#include "ui_config.h"


/*
 ##########################################################
 #####                                                #####
 #####  GUI Seiter zur erstellung der Konfig Datei    #####
 #####                                                #####
 ##########################################################
 */


QString settings[24];
QString can_old;
QLineEdit *conf_line[8], *conf_line_slide[8], *conf_line_digital[8], *output_line[8], *output_line_bed[8];
QSlider   *conf_slider[8];
QComboBox * output_combo_ab[8], *output_combo_ver[8], *analog_sensor[8];
QStringList combo_names;



config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);

    startup();
}

config::~config()
{
    delete ui;
}


//----------Funktion zum Speichern der Analogwerte----------//
//Namensfelder und Slider werden eingelesen und in einen Array gespeichert
//dieser Array wird über die Funktion set_ad_config synchronisiert//
void config::on_button_analog_upload_clicked()
{
    for(int i = 0; i < 8; i++)
    {
        settings[i] = conf_line[i]->text();
    }
    for(int i = 0; i < 8; i++)
    {
        settings[i+8] = QString::number(conf_slider[i]->value());
    }
    for(int i = 0; i < 8; i++)
    {
        settings[i+16] = QString::number(analog_sensor[i]->currentIndex());
    }

    data.set_ad_config(false,settings); //false = analog, true = digital
    refresh();

}


//----------Funktion zur Vorbereitung des GUI's----------//
//GUI Elemente in Arrays speichern zur einfacheren Verarbeitung
void config::startup()
{
    //Sensortypen speichern
    sensornames.append("Druck");
    sensornames.append("Temperatur");

    //Namensfelder für Analogports in Array speichern
    conf_line[0] = ui->conf_line_analog_0;
    conf_line[1] = ui->conf_line_analog_1;
    conf_line[2] = ui->conf_line_analog_2;
    conf_line[3] = ui->conf_line_analog_3;
    conf_line[4] = ui->conf_line_analog_4;
    conf_line[5] = ui->conf_line_analog_5;
    conf_line[6] = ui->conf_line_analog_6;
    conf_line[7] = ui->conf_line_analog_7;

    //Slider zur Messzeitfestlegung für Analogports in Array speichern
    conf_slider[0] = ui->conf_slid_analog_0;
    conf_slider[1] = ui->conf_slid_analog_1;
    conf_slider[2] = ui->conf_slid_analog_2;
    conf_slider[3] = ui->conf_slid_analog_3;
    conf_slider[4] = ui->conf_slid_analog_4;
    conf_slider[5] = ui->conf_slid_analog_5;
    conf_slider[6] = ui->conf_slid_analog_6;
    conf_slider[7] = ui->conf_slid_analog_7;

    //Slider zur Messzeitfestlegung für Digitalports in Array speichern
    conf_line_slide[0] = ui->conf_line_slide_0;
    conf_line_slide[1] = ui->conf_line_slide_1;
    conf_line_slide[2] = ui->conf_line_slide_2;
    conf_line_slide[3] = ui->conf_line_slide_3;
    conf_line_slide[4] = ui->conf_line_slide_4;
    conf_line_slide[5] = ui->conf_line_slide_5;
    conf_line_slide[6] = ui->conf_line_slide_6;
    conf_line_slide[7] = ui->conf_line_slide_7;

    //Namensfelder für Digitalports in Array speichern
    conf_line_digital[0] = ui->conf_line_digital_0;
    conf_line_digital[1] = ui->conf_line_digital_1;
    conf_line_digital[2] = ui->conf_line_digital_2;
    conf_line_digital[3] = ui->conf_line_digital_3;
    conf_line_digital[4] = ui->conf_line_digital_4;
    conf_line_digital[5] = ui->conf_line_digital_5;
    conf_line_digital[6] = ui->conf_line_digital_6;
    conf_line_digital[7] = ui->conf_line_digital_7;

    //Namensfelder für Ausgangsports in Array speichern
    output_line[0] = ui->conf_line_output_0;
    output_line[1] = ui->conf_line_output_1;
    output_line[2] = ui->conf_line_output_2;
    output_line[3] = ui->conf_line_output_3;
    output_line[4] = ui->conf_line_output_4;
    output_line[5] = ui->conf_line_output_5;
    output_line[6] = ui->conf_line_output_6;
    output_line[7] = ui->conf_line_output_7;

    //Bedingung für Ausgangsports in Array speichern
    output_line_bed[0] = ui->output_line_bed_0;
    output_line_bed[1] = ui->output_line_bed_1;
    output_line_bed[2] = ui->output_line_bed_2;
    output_line_bed[3] = ui->output_line_bed_3;
    output_line_bed[4] = ui->output_line_bed_4;
    output_line_bed[5] = ui->output_line_bed_5;
    output_line_bed[6] = ui->output_line_bed_6;
    output_line_bed[7] = ui->output_line_bed_7;

    //Abhängigkeit (Verknüpfter Port)
    output_combo_ab[0] = ui->output_combo_0;
    output_combo_ab[1] = ui->output_combo_1;
    output_combo_ab[2] = ui->output_combo_2;
    output_combo_ab[3] = ui->output_combo_3;
    output_combo_ab[4] = ui->output_combo_4;
    output_combo_ab[5] = ui->output_combo_5;
    output_combo_ab[6] = ui->output_combo_6;
    output_combo_ab[7] = ui->output_combo_7;

    //Verknüpfung (<,>,=...>
    output_combo_ver[0] = ui->output_combo_verkn_0;
    output_combo_ver[1] = ui->output_combo_verkn_1;
    output_combo_ver[2] = ui->output_combo_verkn_2;
    output_combo_ver[3] = ui->output_combo_verkn_3;
    output_combo_ver[4] = ui->output_combo_verkn_4;
    output_combo_ver[5] = ui->output_combo_verkn_5;
    output_combo_ver[6] = ui->output_combo_verkn_6;
    output_combo_ver[7] = ui->output_combo_verkn_7;

    //Sensorliste
    analog_sensor[0] = ui->analog_combo_sensor_0;
    analog_sensor[1] = ui->analog_combo_sensor_1;
    analog_sensor[2] = ui->analog_combo_sensor_2;
    analog_sensor[3] = ui->analog_combo_sensor_3;
    analog_sensor[4] = ui->analog_combo_sensor_4;
    analog_sensor[5] = ui->analog_combo_sensor_5;
    analog_sensor[6] = ui->analog_combo_sensor_6;
    analog_sensor[7] = ui->analog_combo_sensor_7;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < sensornames.length();j++)
        {
            analog_sensor[i]->addItem(sensornames.at(j));
        }
    }

    combo_names = data.load_names();    //lädt alle Bezeichnungen der Analog und Digital Ports

    ui->tabWidget->setCurrentIndex(0);  //Schaltet auf die erste Seite (Analogwerte)

    //data.connect();
    data.get_ad_config(false,settings); //Lädt alle Analog Einstelluungen
    //------------------Startup Analog-----------------------//

    for(int i = 0; i < 8; i++)  //Schreibt die Werte aus der DB in die Namensfelder Analog
    {
        conf_line[i]->setText(settings[i]);
    }
    for(int i = 0; i < 8; i++)  //Setzt die Slider auf die Werte aus der DB
    {
        conf_slider[i]->setValue(settings[i+8].toInt());
        conf_line_slide[i]->setText(settings[i+8]);
    }
    for(int i = 0; i < 8; i++)  //Setzt die Slider auf die Werte aus der DB
    {
        analog_sensor[i]->setCurrentIndex(settings[i+16].toInt());
    }

    data.get_ad_config(true,settings); //Lädt alle Digital Einstelluungen

    for(int i = 0; i < 8; i++) //Schreibt die Werte aus der DB in die Namensfelder Digital
    {
        conf_line_digital[i]->setText(settings[i]);
    }


    //----------Schreibt alle vorhandenen CAN Konfigurationen in die Tabelle
    data.get_can_model(can_modal);
    ui->tableView_can->setModel(can_modal);
    ui->tableView_can->setColumnWidth(0,ui->tableView_can->width()/2-2);
    ui->tableView_can->setColumnWidth(1,ui->tableView_can->width()/2-2);
    ui->tableView_can->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
    ui->tableView_can->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_can->setSelectionMode(QAbstractItemView::SingleSelection);

    for(int i = 0; i < 8; i++)  //Setzt die Verknüfpungen für die Ausgangsverknüpfung
    {
        output_combo_ver[i]->addItem("<");
        output_combo_ver[i]->addItem(">");
        output_combo_ver[i]->addItem("=");
        output_combo_ver[i]->addItem("!=");
    }

    for(int i = 0; i < 8; i++)  //Schreibt alle Digitalen und Analogen Bezeichnungen in die Combo Box zur Ausgangsverknüpfung
    {
        for(int j = 0; j < 16; j++)
        {
          output_combo_ab[i]->addItem(combo_names.at(j));
        }
    }

    QStringList output_bezeichnungen;
    int output_bed[8], output_ver[8], output_ab[8];
    data.get_output_config(output_bezeichnungen,output_ab,output_ver,output_bed);

    for(int i = 0; i < 8; i++)  //Schreibt die Werte aus der DB in die Ausgangskonfiguration
    {
        qDebug() << i;
        output_line[i]->setText(output_bezeichnungen.at(i));
        output_combo_ab[i]->setCurrentIndex(output_ab[i]);
        output_combo_ver[i]->setCurrentIndex(output_ver[i]);
        output_line_bed[i]->setText(QString::number(output_bed[i]));
    }
}

//-----------Funktion zur aktualisierung des GUI's nach Wertänderung-------------//
//To Do : Nur geänderte Werte aktualisieren
void config::refresh()
{

    combo_names = data.load_names();
    data.get_ad_config(false,settings);
    //------------------Startup Analog-----------------------//

    for(int i = 0; i < 8; i++)
    {
        conf_line[i]->setText(settings[i]);
    }
    for(int i = 0; i < 8; i++)
    {
        conf_slider[i]->setValue(settings[i+8].toInt());
        conf_line_slide[i]->setText(settings[i+8]);
    }
    data.get_ad_config(true,settings);
    for(int i = 0; i < 8; i++)
    {
        conf_line_digital[i]->setText(settings[i]);
    }

    data.get_can_model(can_modal);
    ui->tableView_can->setModel(can_modal);
    ui->tableView_can->setColumnWidth(0,ui->tableView_can->width()/2-2);
    ui->tableView_can->setColumnWidth(1,ui->tableView_can->width()/2-2);
    ui->tableView_can->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
    ui->tableView_can->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_can->setSelectionMode(QAbstractItemView::SingleSelection);

    for(int i = 0; i < 8; i++)
    {
        output_combo_ab[i]->clear();
        for(int j = 0; j < 16; j++)
        {
          output_combo_ab[i]->addItem(combo_names.at(j));
        }
    }

    QStringList output_bezeichnungen;
    int output_bed[8], output_ver[8], output_ab[8];
    data.get_output_config(output_bezeichnungen,output_ab,output_ver,output_bed);

    for(int i = 0; i < 8; i++)
    {
        qDebug() << i;
        output_line[i]->setText(output_bezeichnungen.at(i));
        output_combo_ab[i]->setCurrentIndex(output_ab[i]);
        output_combo_ver[i]->setCurrentIndex(output_ver[i]);
        output_line_bed[i]->setText(QString::number(output_bed[i]));
    }
}

//-----------------Verknüpfung zwischen Slider und Textfeldern-------------------//
//Bei Änderung eines Sliders soll der Wert in das Textfeld eingetragen werden
//Bei Änderung eines Textfeldes wird der Wert des Sliders angepasst
void config::on_conf_slid_analog_6_sliderMoved(int position)
{
    conf_line_slide[6]->setText(QString::number(conf_slider[6]->value()));
}

void config::on_conf_slid_analog_7_sliderMoved(int position)
{
    conf_line_slide[7]->setText(QString::number(conf_slider[7]->value()));
}

void config::on_conf_slid_analog_5_sliderMoved(int position)
{
    conf_line_slide[5]->setText(QString::number(conf_slider[5]->value()));
}

void config::on_conf_slid_analog_4_sliderMoved(int position)
{
    conf_line_slide[4]->setText(QString::number(conf_slider[4]->value()));
}

void config::on_conf_slid_analog_3_sliderMoved(int position)
{
    conf_line_slide[3]->setText(QString::number(conf_slider[3]->value()));
}

void config::on_conf_slid_analog_2_sliderMoved(int position)
{
    conf_line_slide[2]->setText(QString::number(conf_slider[2]->value()));
}

void config::on_conf_slid_analog_1_sliderMoved(int position)
{
    conf_line_slide[1]->setText(QString::number(conf_slider[1]->value()));
}

void config::on_conf_slid_analog_0_sliderMoved(int position)
{
    conf_line_slide[0]->setText(QString::number(conf_slider[0]->value()));
}

void config::on_conf_line_slide_0_editingFinished()
{
    conf_slider[0]->setValue(conf_line_slide[0]->text().toInt());
}

void config::on_conf_line_slide_1_editingFinished()
{
    conf_slider[1]->setValue(conf_line_slide[1]->text().toInt());
}

void config::on_conf_line_slide_2_editingFinished()
{
    conf_slider[2]->setValue(conf_line_slide[2]->text().toInt());
}

void config::on_conf_line_slide_3_editingFinished()
{
    conf_slider[3]->setValue(conf_line_slide[3]->text().toInt());
}

void config::on_conf_line_slide_4_editingFinished()
{
    conf_slider[4]->setValue(conf_line_slide[4]->text().toInt());
}

void config::on_conf_line_slide_5_editingFinished()
{
    conf_slider[5]->setValue(conf_line_slide[5]->text().toInt());
}

void config::on_conf_line_slide_6_editingFinished()
{
    conf_slider[6]->setValue(conf_line_slide[6]->text().toInt());
}

void config::on_conf_line_slide_7_editingFinished()
{
    conf_slider[7]->setValue(conf_line_slide[7]->text().toInt());
}

//--------------------Knöpfe zur Seitenumschaltung---------------------//

void config::on_button_next_digital_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void config::on_button_prev_analog_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void config::on_button_next_can_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void config::on_button_prev_digital_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void config::on_button_next_output_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void config::on_button_prev_can_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

//---------Funktion zum speichern der Digitalwerte in der DB------------//
//Werte werden aus GUI geladen und mit DB synchronisiert
void config::on_button_digital_upload_clicked()
{
    for(int i = 0; i < 8; i++)
    {
        settings[i] = conf_line_digital[i]->text();
    }
    for(int i = 0; i < 8; i++)
    {
        settings[i+8] = QString::number(0);
    }

    data.set_ad_config(true,settings);
    refresh();
}


//-------------Funktion zum Hinzufügen einer neuen CAN-Config-------------//
//Die Liste ist Model based, das bedeutet es können keine Daten direkt hinzugefügt werden
//nur durch eintragen eines Wertes in die DB ist das möglich.
void config::on_button_add_clicked()
{
   QString add[2];

   add[0] = ui->line_bezeichnung->text();
   add[1] = ui->line_message->text();
   data.add_can(add);
   ui->line_bezeichnung->setText("");
   ui->line_message->setText("");

   data.get_can_model(can_modal);
   ui->tableView_can->setModel(can_modal);

   refresh();

}

//------------------Funktion zum löschen eines CAN-Wertes-----//
void config::on_button_can_delete_clicked()
{
   data.remove_can(ui->line_bezeichnung->text());

   data.get_can_model(can_modal);
   ui->tableView_can->setModel(can_modal);
   refresh();
}

//Wenn ein Wert in der Tabelle ausgewählt wird, werden der Name und die Nachricht
//In den beiden extrigen Feldern eingetragen
void config::on_tableView_can_activated(const QModelIndex &index)
{
    QString name;
    name = ui->tableView_can->model()->data(index).toString();
    ui->line_bezeichnung->setText(name);
    ui->line_message->setText(data.get_can_message(name));
    can_old = name;
}

//Die Werte in den extrigen Feldern werden geändert
//An die Funktion wird der neue Name und Nachricht gesendet,
//und der alte Name damit die Nachricht identifiziert werden kann
void config::on_button_edit_clicked()
{
    QString ed_can[3];
    ed_can[0] = ui->line_bezeichnung->text();
    ed_can[1] = ui->line_message->text();
    ed_can[2] = can_old;
    data.edit_can(ed_can);

    data.get_can_model(can_modal);
    ui->tableView_can->setModel(can_modal);
}


//Die Konfiguration der Ausgangskonfig in die DB speichern.
void config::on_button_output_upload_clicked()
{
    QStringList bezeichnungen;
    int ab[8], ver[8], bed[8];

    for(int i = 0; i < 8; i++)
    {
        bezeichnungen.append(output_line[i]->text());
    }


    for(int i = 0; i < 8; i++)
    {
        ab[i] = output_combo_ab[i]->currentIndex();
        ver[i] = output_combo_ver[i]->currentIndex();
        bed[i] = output_line_bed[i]->text().toInt();

    }

    data.set_output_config(bezeichnungen, ab, ver, bed);
}
