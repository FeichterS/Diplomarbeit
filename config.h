#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include "database.h"

/*
 ##########################################################
 #####                                                #####
 #####  GUI Seiter zur erstellung der Konfig Datei    #####
 #####                                                #####
 ##########################################################
 */

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = 0);
    database data;
    QSqlQueryModel *can_modal=new QSqlQueryModel();
    QStringList sensornames;
    ~config();

private slots:
    void startup();
    void refresh();

    void on_button_analog_upload_clicked();
    void on_conf_slid_analog_6_sliderMoved(int position);
    void on_conf_slid_analog_7_sliderMoved(int position);
    void on_conf_slid_analog_5_sliderMoved(int position);
    void on_conf_slid_analog_4_sliderMoved(int position);
    void on_conf_slid_analog_3_sliderMoved(int position);
    void on_conf_slid_analog_2_sliderMoved(int position);
    void on_conf_slid_analog_1_sliderMoved(int position);
    void on_conf_slid_analog_0_sliderMoved(int position);
    void on_conf_line_slide_0_editingFinished();
    void on_conf_line_slide_1_editingFinished();
    void on_conf_line_slide_2_editingFinished();
    void on_conf_line_slide_3_editingFinished();
    void on_conf_line_slide_4_editingFinished();
    void on_conf_line_slide_5_editingFinished();
    void on_conf_line_slide_6_editingFinished();
    void on_conf_line_slide_7_editingFinished();
    void on_button_next_digital_clicked();
    void on_button_prev_analog_clicked();
    void on_button_next_can_clicked();
    void on_button_prev_digital_clicked();
    void on_button_next_output_clicked();
    void on_button_prev_can_clicked();
    void on_button_digital_upload_clicked();
    void on_button_add_clicked();
    void on_button_can_delete_clicked();
    void on_tableView_can_activated(const QModelIndex &index);
    void on_button_edit_clicked();
    void on_button_output_upload_clicked();

private:
    Ui::config *ui;
};

#endif // CONFIG_H
