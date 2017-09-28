#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QTcpSocket>
#include <database.h>

/*
 ##########################################################
 #####                                                #####
 #####    Funktionen zur Kommunikation über UDP/TCP   #####
 #####                                                #####
 ##########################################################
 */

#define PORT_UDP     800
#define PORT_TCP     801

class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = 0);
    void HelloUDP();
    void send_settings(int[]);
    QTcpSocket *tcp_socket;
    bool error = false;


signals:
    void readyPlot(QVector<double>,QVector<int>);
public slots:
    void readyRead();



private:
    QUdpSocket *udp_socket;
    QVector<int> current_digital;
    QVector<double> current_analog;
    QHostAddress IP;


    void seperate_msg(QByteArray);

};
#endif // NETWORK_H

//Message Format//
// Analog0:Analog1:Analog2:Analog3:Analog4:Analog5:Analog6:Analog7:Digital0:Digital1:Digital2:Digital3:Digital4:Digital5:Digital6:Digital7:
