#ifndef MESSDATEN_H
#define MESSDATEN_H

#include <QDialog>
#include "database.h"

/*
 ##########################################################
 #####                                                #####
 #####   GUI Seite zur Visualisierung der Messdaten   #####
 #####                                                #####
 ##########################################################
 */

namespace Ui {
class Messdaten;
}

class Messdaten : public QDialog
{
    Q_OBJECT

public:
    explicit Messdaten(QWidget *parent = 0);
    ~Messdaten();
    database data;
    QVector<can_data> can_values;

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_checkBox_clicked();

    void on_button_delete_clicked();

    void on_combo_values_activated(int index);

    void on_calender_start_clicked(const QDate &date);

    void on_time_start_timeChanged(const QTime &time);

    void on_time_end_timeChanged(const QTime &time);

    void can_value_refresh();

    void on_button_delete_can_clicked();

    void on_check_can_clicked();

private:
    Ui::Messdaten *ui;
};

#endif // MESSDATEN_H
