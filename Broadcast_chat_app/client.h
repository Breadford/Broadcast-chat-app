#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QMap>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include <iostream>
using namespace std;

class client : public QObject{
    Q_OBJECT
private:
    char* user_name;
    quint8 count = 0;                               /*Brojac poslatih beacona kojim proveravamo klijente u mrezi*/
    QUdpSocket *UDPsocket;
    QHostAddress *ip_address;                       /*IP adresa clienta*/
    QHostAddress *ip_broadcast;                     /*Adresa za broadcast*/
    QMap<QByteArray, QByteArray> users, old_user;    /*Mapa koja cuva liste usera novih i starih*/

    void reg_response(QHostAddress address);
    void user_response(QHostAddress address, char* buff, int rd_cnt);
    void msg_response(QHostAddress address, char* buff, int rd_cnt);

public:
    client();

private slots:
        void send_msg();
        void usr_reg();
        void datagram_types();


};

#endif // CLIENT_H
