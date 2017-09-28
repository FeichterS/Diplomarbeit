#include "messdaten.h"
#include "ui_messdaten.h"
#include "database.h"

/*
 ##########################################################
 #####                                                #####
 #####   GUI Seite zur Visualisierung der Messdaten   #####
 #####                                                #####
 ##########################################################
 */

QStringList dates;

Messdaten::Messdaten(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Messdaten)
{
    ui->setupUi(this);

    data.get_value_dates(dates);
    QStringList can_headings;
    for(int i = 0; i < dates.length(); i++)
    {
        ui->combo_values->addItem(dates.at(i));
    }
    //Tabelle für CAN-Werte vorbereiten
    ui->can_table->setColumnCount(5);
    can_headings << "Nachricht" << "Datum" << "Stunde" << "Minute" << "Sekunde";
    ui->can_table->setHorizontalHeaderLabels(can_headings);
    ui->can_table->setColumnWidth(0,ui->can_table->width()/3);
    ui->can_table->setColumnWidth(1,ui->can_table->width()/3);
    ui->can_table->setColumnWidth(2,ui->can_table->width()/3);
    ui->can_table->setSelectionMode(QAbstractItemView::MultiSelection);
}

Messdaten::~Messdaten()
{
    delete ui;
}

//----------Wenn eine Messung ausgewählt wird, sollen die Werte in die Textfelder geladen werden
void Messdaten::on_combo_values_activated(int index)
{
    QStringList analog, digital, date;


    if(ui->checkBox->checkState())
    {
        for(int i = 0; i < dates.length(); i++)
        {
            if(ui->combo_values->itemText(index) == dates.at(i))
                index = i;
        }
    }
    data.get_values(index, analog, digital, date); //Werte aus der DB laden

    //Werte in die Felder schreiben
    //To Do : Alle Felder in Arrays speichern um schleifen nutzen zu können
    ui->analog_0->setText(analog.at(0));
    ui->analog_1->setText(analog.at(1));
    ui->analog_2->setText(analog.at(2));
    ui->analog_3->setText(analog.at(3));
    ui->analog_4->setText(analog.at(4));
    ui->analog_5->setText(analog.at(5));
    ui->analog_6->setText(analog.at(6));
    ui->analog_7->setText(analog.at(7));

    ui->digital_0->setText(digital.at(0));
    ui->digital_1->setText(digital.at(1));
    ui->digital_2->setText(digital.at(2));
    ui->digital_3->setText(digital.at(3));
    ui->digital_4->setText(digital.at(4));
    ui->digital_5->setText(digital.at(5));
    ui->digital_6->setText(digital.at(6));
    ui->digital_7->setText(digital.at(7));

    ui->line_date->setText(date.at(0));
    ui->line_time->setText(date.at(1));

}

//
void Messdaten::on_calendarWidget_clicked(const QDate &date)
{
    if(ui->checkBox->checkState())
    {
        QString calender;
        QString day, month;
        //-----------------------------Datum auf dd.mm.yyyy formatieren------------------------//
        if(date.day() < 10)
            day = "0" + QString::number(date.day());
        else
            day = QString::number(date.day());
        if(date.month() < 10)
            month = "0" + QString::number(date.month());
        else
            day = QString::number(date.month());

        calender = day + "." +  month + "." + QString::number(date.year());
        //--------------------------------------------------------------------------------//
        ui->combo_values->clear();
        data.get_value_dates(dates);
        int length = calender.length();

        for(int i = 0; i < dates.length(); i++)
        {
            if(dates.at(i).left(length) == calender.left(length))
            {
                ui->combo_values->addItem(dates.at(i));
            }
        }
    }


}

void Messdaten::on_checkBox_clicked()
{
    if(!ui->checkBox->checkState())
    {
        ui->combo_values->clear();
        data.get_value_dates(dates);
        qDebug() << dates;
        for(int i = 0; i < dates.length(); i++)
        {
            ui->combo_values->addItem(dates.at(i));
        }
    }
}

void Messdaten::on_button_delete_clicked()
{
    data.delete_value(ui->combo_values->currentIndex());
    ui->combo_values->clear();
    data.get_value_dates(dates);
    qDebug() << dates;
    for(int i = 0; i < dates.length(); i++)
    {
        ui->combo_values->addItem(dates.at(i));
    }
}

void Messdaten::on_calender_start_clicked(const QDate &date)
{
    can_value_refresh();
}

void Messdaten::on_time_start_timeChanged(const QTime &time)
{
   can_value_refresh();
}

void Messdaten::on_time_end_timeChanged(const QTime &time)
{
    can_value_refresh();
}

void Messdaten::can_value_refresh()
{
    if(!ui->checkBox->checkState())
    {
        ui->can_table->setRowCount(0);
        QString can_date, day, month;
        QString start_hour, start_minute, end_hour, end_minute;
        int start_time, end_time, current_time;
        data.get_can_values(can_values);

        if(ui->calender_start->selectedDate().day() < 10)
            day = "0" + QString::number(ui->calender_start->selectedDate().day());
        else
            day = QString::number(ui->calender_start->selectedDate().day());
        if(ui->calender_start->selectedDate().month() < 10)
            month = "0" + QString::number(ui->calender_start->selectedDate().month());
        else
            day = QString::number(ui->calender_start->selectedDate().month());

        can_date = day + "." + month + "." + QString::number(ui->calender_start->selectedDate().year());

        start_time = 60*ui->time_start->time().hour() + ui->time_start->time().minute();
        end_time   = 60*ui->time_end->time().hour() + ui->time_end->time().minute();

        for(int i = 0; i < can_values.length();i++)
        {
            current_time = 60*can_values.at(i).can_hour.toInt() + can_values.at(i).can_minute.toInt();
            if(can_values.at(i).can_date == can_date)
            {
                if(current_time > start_time && current_time < end_time)
                {
                    ui->can_table->setRowCount(ui->can_table->rowCount()+1);
                    ui->can_table->setItem(ui->can_table->rowCount()-1,0,new QTableWidgetItem(can_values.at(i).can_message));
                    ui->can_table->setItem(ui->can_table->rowCount()-1,1,new QTableWidgetItem(can_values.at(i).can_date));
                    ui->can_table->setItem(ui->can_table->rowCount()-1,2,new QTableWidgetItem(can_values.at(i).can_hour + ":" + can_values.at(i).can_minute + ":" + can_values.at(i).can_second));
                }
            }
        }
    }
}

void Messdaten::on_button_delete_can_clicked()
{
    QModelIndexList indexes;
    indexes=ui->can_table->selectionModel()->selectedRows();
    for(int i = 0; i < indexes.length();i++)
    {
        data.delete_can_values(ui->can_table->item(ui->can_table->currentRow(),0)->text(),ui->can_table->item(ui->can_table->currentRow(),1)->text(),ui->can_table->item(ui->can_table->currentRow(),2)->text());
        ui->can_table->removeRow(ui->can_table->currentRow());
    }

}

void Messdaten::on_check_can_clicked()
{

    if(ui->check_can->checkState())
    {
        data.get_can_values(can_values);
        for(int i = 0; i < can_values.length();i++)
        {
            ui->can_table->setRowCount(ui->can_table->rowCount()+1);
            ui->can_table->setItem(ui->can_table->rowCount()-1,0,new QTableWidgetItem(can_values.at(i).can_message));
            ui->can_table->setItem(ui->can_table->rowCount()-1,1,new QTableWidgetItem(can_values.at(i).can_date));
            ui->can_table->setItem(ui->can_table->rowCount()-1,2,new QTableWidgetItem(can_values.at(i).can_hour + ":" + can_values.at(i).can_minute + ":" + can_values.at(i).can_second));
        }
    }
}
