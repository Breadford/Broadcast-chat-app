#include <QCoreApplication>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include <QList>
#include <QThread>
#include <iostream>
#include <reg_thread.h>
#include <message_thread.h>
#include <client.h>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    client client1;
    message_thread messageCall;
    reg_thread regCall;

    regCall.start();
    messageCall.start();

    QObject::connect(&regCall, SIGNAL(binterupt()), &client1, SLOT(usr_reg()), Qt::DirectConnection);
    QObject::connect(&messageCall, SIGNAL(enter_message()), &client1, SLOT(send_msg()), Qt::DirectConnection);

    return a.exec();
}
