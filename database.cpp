#include "database.h"

/*
 ##########################################################
 #####                                                #####
 ##### Funktionen zur kommunikation mit der Datenbank #####
 #####                                                #####
 ##########################################################
 */

//############Probleme######################//
//------------Crash der db-----------------//
//db wurde mehrmals geöffnet ohne sie zu schließen


database::database()
{

}

//---------Verbindung mit db herstellen---------------//
//Verbindung für Konfigurationsdateien
bool database::connect()
{
    db_config.setHostName(hostname);
    db_config.setUserName(username);
    db_config.setPassword(pw);
    db_config.setDatabaseName(dbname);

    query_config = new QSqlQuery(db_config);

    if(db_config.open())
        qDebug() << "connectet";
    else
        return false;
}

//---------Verbindung mit db herstellen---------------//
//Verbindung für Werte
bool database::values_connect()
{
    db_values.setHostName(hostname);
    db_values.setUserName(username);
    db_values.setPassword(pw);
    db_values.setDatabaseName(dbname_values);

    query_values = new QSqlQuery(db_values);

    if(db_values.open())
        qDebug() << "db_values connected";
    else
    {
        qDebug() << "db_values Error";
        return false;
    }
}

//------Die Konfiguration für Analog und Digital Ports abfragen
//true -> digital
//false -> analog
//Die Portbezeichnungen werden in den ersten 8 Array Elementen gespeichert
//Die Messzeit in den zweiten 8 Array Elementen
void database::get_ad_config(bool digital, QString ret[])
{
    connect();
    QString bez[8];
    QString time[8];
    QString sensor[8] = {0};

    if(digital == true)
        query_config->prepare("SELECT * FROM digital");
    else
        query_config->prepare("SELECT * FROM analog");

     query_config->exec();
     query_config->first();

    for(int i = 0; i < 8; i++)
    {
        bez[i] = query_config->value(1).toString().toUtf8().constData();    //Werte aus der db laden
        time[i] = query_config->value(2).toString().toUtf8().constData();
        if(digital == false)
            sensor[i] = query_config->value(3).toString().toUtf8().constData();
        query_config->next();
    }


    for(int c = 0; c < 8; c++)      //Bezeichnungen und Messzeiten in ein Array speichern
        ret[c] = bez[c];
    for(int c = 8; c < 16; c++)
        ret[c] = time[c-8];
    for(int c = 16; c < 24; c++)
        ret[c] = sensor[c-16];

    db_config.close();
}

//---------Funktion um die Bezeichnungen der Analog und Digital Ports zu laden
//Ersten 8 Werte Analog
//Zweiten 8 Werte Digital
QStringList database::load_names()
{
    connect();

    QStringList names;
    query_config->prepare("SELECT * FROM analog");
    query_config->exec();
    query_config->first();

    for(int i = 0; i < 8; i++)
    {
        names.append(query_config->value(1).toString().toUtf8().constData());
        query_config->next();
    }

    query_config->prepare("SELECT * FROM digital");
    query_config->exec();
    query_config->first();

    for(int i = 0; i < 8; i++)
    {
        names.append(query_config->value(1).toString().toUtf8().constData());
        query_config->next();
    }

db_config.close();
return names;
}

//--------Neue CAN-Nachrichten definieren------------
//Wert 0: Bezeichnung
//Wert 1: Nachricht
void database::add_can(QString can[])
{
    connect();
    query_config->prepare("SELECT * FROM can");


    query_config->prepare("insert into can (Bezeichnung,message)"
                          "VALUES (:bez, :message)");
        query_config->bindValue(":bez",can[0]);
        query_config->bindValue(":message",can[1]);
        query_config->exec();

        db_config.close();

}


//-----------CAN-Nachricht löschen----------------------
//Bezeichnung der Nachricht wird übergeben
void database::remove_can(QString bez)
{
    connect();
    query_config->prepare("DELETE FROM can WHERE Bezeichnung = :b");
    query_config->bindValue(":b",bez);
    query_config->exec();
    db_config.close();
}

//----------------Gibt die CAN Nachricht mit der Übergebenen Adresse zurück
QString database::get_can_message(QString bez)
{
    connect();
    int i = 0;
    query_config->prepare("SELECT * FROM can where Bezeichnung ='"+bez+"'");
    query_config->exec();
    query_config->first();
   while(i != 1)
   {
       if(query_config->value(0).toString() == bez)
           return query_config->value(1).toString();
       query_config->next();
   }

   db_config.close();

}

//------------Übergibt die IP Adresse des Raspperrys um eine TCP Verbindung zu ermöglichen
QString database::getIp()
{
    QString buffer;

    connect();
    query_config->prepare("SELECT * FROM general ");
    query_config->exec();
    query_config->first();
    buffer = query_config->value(0).toString();
    db_config.close();
    return buffer;
}

//-----------CAN-Nachricht editieren
//Eine Bezeichnung oder Nachricht editieren
//Zur findung der richtigen Nachricht wird die alte Bezeichnung genutzt
void database::edit_can(QString can[])
{
    connect();
    query_config->prepare("update can set Bezeichnung = :b, message = :mes where Bezeichnung = :b_old");
    query_config->bindValue(":b",can[0]);
    query_config->bindValue(":mes",can[1]);
    query_config->bindValue(":b_old",can[2]);
    query_config->exec();

    db_config.close();
}

//---Funktion um die AD konfiguration zu setzen
//true = digital
//false = analog
void database::set_ad_config(bool digital, QString settings[])
{
    connect();
    QString bez[8];
    QString time[8];

    for(int i = 0; i < 8; i++)
    {

        if(digital == true)
            query_config->prepare("update digital set ID = :i, Bezeichnung = :bez , Messdauer = :time where digital.ID = :i ");
        else
            query_config->prepare("update analog set ID = :i, Bezeichnung = :bez , Messdauer = :time , Sensortype = :sensor where analog.ID = :i ");
        query_config->bindValue(":i",i);
        query_config->bindValue(":bez",settings[i]);
        query_config->bindValue(":time",settings[i+8]);
        if(digital == false)
            query_config->bindValue(":sensor",settings[i+16]);
        query_config->exec();

    }

    db_config.close();
}

//--------Konfiguration für die Ausgänge
//bez : Bezeichnung des Ausganges
//ab  : Port von den der Ausgang abhängig ist
//ver : Verknüpfung (<,>,=,!=)
//bed : Bedingung z.B Analog3 < 8
void database::set_output_config(QStringList bez, int ab[], int ver[], int bed[])
{
    connect();

    for(int i = 0; i < 8; i++)
    {
        query_config->prepare("update output set ID = :id, Bezeichnung = :b , Abhaengigkeit = :a, Verknuepfung =:v, Bedingung =:be where output.ID = :id ");
        query_config->bindValue(":id",i);
        query_config->bindValue(":b",bez.at(i));
        query_config->bindValue(":a",QString::number(ab[i]));
        query_config->bindValue(":v",QString::number(ver[i]));
        query_config->bindValue(":be",QString::number(bed[i]));
        query_config->exec();
    }
    db_config.close();
}

//---------modal für die CAN Tabelle
//Verknüpfung zwischen Tabelle und Datenbank
//Die Tabelle kann nicht geändert werden, nur die DB
void database::get_can_model(QSqlQueryModel *modal)
{
    connect();
    //QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(db_config);
    qry->prepare("select * from can");
    qry->exec();
    modal->setQuery(*qry);

    db_config.close();
}

//--------Funktion zur Rückgabe der Output Konfiguration
//bez : Bezeichnung des Ausganges
//ab  : Port von den der Ausgang abhängig ist
//ver : Verknüpfung (<,>,=,!=)
//bed : Bedingung z.B Analog3 < 8
void database::get_output_config(QStringList &bez, int ab[], int ver[], int bed[])
{
    connect();

    query_config->prepare("SELECT * FROM output");
    query_config->exec();
    query_config->first();

    for(int i = 0; i < 8; i++)
    {
        bez.append(query_config->value(1).toString());
        ab[i] = query_config->value(2).toInt();
        ver[i] = query_config->value(3).toInt();
        bed[i] = query_config->value(4).toInt();

        query_config->next();
    }

    db_config.close();
}

//---------Messwerte Analog und Digital laden
//Abfrage über eine ID (mit ID in Combo Box identisch)
void database::get_values(int id, QStringList &analog, QStringList &digital, QStringList &date)
{
    values_connect();
    query_values->prepare("SELECT * FROM val where id = :i");
    query_values->bindValue(":i",id);
    query_values->exec();
    query_values->first();
    for(int i = 0; i < 8; i++)
    {
        analog.append(query_values->value(i+1).toString()); //Analogwerte
    }
    for(int i = 0; i < 8; i++)
    {
        digital.append(query_values->value(i+9).toString()); //Digitalwerte
    }
    for(int i = 0; i < 2; i++)
    {
        date.append(query_values->value(i+17).toString()); //Datum
    }

    db_values.close();
}

//------Funktion die alle Daten/Uhrzeiten zurück gibt an denen es eine Messung gab
void database::get_value_dates(QStringList &dates)
{
    values_connect();
    query_values->prepare("SELECT * FROM val");
    query_values->exec();
    query_values->first();

    dates.clear();

    do
    {
        dates.append(query_values->value(17).toString() + ":" + query_values->value(18).toString());

            qDebug() << "test";

    }while(query_values->next());

    db_values.close();
}

//-------Löschen von Werten
//Identifizierung über ID
void database::delete_value(int delete_id)
{
    values_connect();
    query_values->prepare("delete FROM val where id = :i");
    query_values->bindValue(":i",delete_id);
    query_values->exec();
    db_values.close();
}

//Alle CAN Nachrichten abfragen
void database::get_can_values(QVector<can_data> &data)
{
    data.clear();
    can_data dat;

    values_connect();
    query_values->prepare("SELECT * FROM can_data");
    query_values->exec();
    query_values->first();

    do
    {
        dat.can_message = query_values->value(0).toString();
        dat.can_date = query_values->value(1).toString();
        dat.can_hour = query_values->value(2).toString().left(2);
        dat.can_minute = query_values->value(2).toString().mid(3,2);
        dat.can_second =  query_values->value(2).toString().right(2);
        data.append(dat);

    }while(query_values->next());
    db_values.close();
}

//---CAN Nachricht löschen
void database::delete_can_values(QString message , QString date , QString time)
{
    qDebug() << message << " -- " << date << " -- " << time.left(5);
    values_connect();
    query_values->prepare("delete FROM can_data where message = :msg and date = :d and time = :ti");
    query_values->bindValue(":msg",message);
    query_values->bindValue(":d",date);
    query_values->bindValue(":ti",time.left(5));
    query_values->exec();
    db_values.close();
}



