#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDebug>

/*
 ##########################################################
 #####                                                #####
 ##### Funktionen zur kommunikation mit der Datenbank #####
 #####                                                #####
 ##########################################################
 */

struct can_data{
    QString can_message;
    QString can_date;
    QString can_hour;
    QString can_minute;
    QString can_second;
};


class database
{
public:
    database();
    bool connect();
    bool values_connect();
    void get_ad_config(bool digital, QString[]);
    void set_ad_config(bool digital, QString[]);
    void add_can(QString[]);
    QString get_can_message(QString);
    void edit_can(QString[3]);
    void remove_can(QString);
    void get_can_model(QSqlQueryModel*);
    QStringList load_names();
    void set_output_config(QStringList, int[], int[], int[]);
    void get_output_config(QStringList &, int[], int[], int[]);
    QString getIp();
    void getSensors(QStringList &, QVector<int> &, QStringList &);

    void get_values(int, QStringList &, QStringList &, QStringList &);
    void get_value_dates(QStringList &);
    void delete_value(int);

    void get_can_values(QVector<can_data> &);
    void delete_can_values(QString, QString, QString);

    QSqlQuery *query_config;
    QSqlQuery *query_values;

private:
    QSqlDatabase db_config = QSqlDatabase::addDatabase("QMYSQL", "config");
    QString hostname    = "localhost";
    QString dbname      = "telematrix_conf";
    QString username    = "root";
    QString pw          = "";

    QSqlDatabase db_values  = QSqlDatabase::addDatabase("QMYSQL", "values");
    QString dbname_values  = "telematrix_data";



    QSqlQuery *query_data;
};

#endif // DATABASE_H
