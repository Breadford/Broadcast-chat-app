#include <client.h>
#include <string.h>
#include <QThread>
#include <stdio.h>
#include <iostream>


char* enter_username(){
    char* buffer = (char*) malloc (20);
    cout << "Enter your username: ";
    cin >> buffer;
    return buffer;
}

char* enter_ip(){
    char* buffer = (char*) malloc (20);
    cout << "Enter your IP: ";
    cin >> buffer;
    return buffer;
}

void enter_msg(char* message){
    cout << "Enter message to send: ";
    cin >> message;
}

client::client(){
   user_name = enter_username();
   ip_address =new QHostAddress(enter_ip());
   ip_broadcast =new QHostAddress("255.255.255.255");
   UDPsocket = new QUdpSocket(this);
   UDPsocket->bind(*ip_address, 27000);
   connect(UDPsocket, SIGNAL(readyRead()), this, SLOT(datagram_types()), Qt::DirectConnection);
}

void client::usr_reg(){   /*Ovo je kao registrator na osnovu koga znamo ko je u mrezi ili je otisao. Na datagramu se lepi prefiks BEACON na osnovu kog se dole u tipu datagrama poziva reg_response*/
    if(count==4){
        QMap<QByteArray, QByteArray>::const_iterator j = users.constBegin();

        while(j != users.constEnd()){              /*Proveravamo ko je dosao u mrezu*/
            if(!old_user.contains(j.key())){
                cout<< endl<<"New user entered /"<<j.value().data()<<"/" << endl << "Enter message to send: ";
            }
            ++j;
        }

        j = old_user.constBegin();

        while (j != old_user.constEnd()){         /*Proveravamo ko je otiso sa mreze*/
            if(!users.contains(j.key())){
                cout << endl << "User /"<< j.value().data() << "/ left network"<< endl << "Enter message to send: ";
            }
            ++j;
        }
        old_user = users;
        users.clear();
        count = 0;

    }

    count++;

    QByteArray to_send;
    to_send.clear();
    to_send.append("USRREG");
    UDPsocket->writeDatagram(to_send, *ip_broadcast, 27000);


}

void client::send_msg(){     /*Slanje poruke, svaki datagram poseduje prefiks MSG= na osnovu koga znamo sta ce da se dogodi dole u tipu datagrama*/
    char message[100];
    enter_msg(message);
    QByteArray to_send;
    to_send.clear();
    to_send.append("MSG=");
    to_send.append(message);
    UDPsocket->writeDatagram(to_send, *ip_broadcast, 27000);
}

void client::msg_response(QHostAddress address, char *buff, int rd_cnt){ /*Poziva se iz tipa datagrama koji je u stvari mozak programa, znamo od koga je dosla poruka*/
    buff[rd_cnt] = '\0';
    QByteArray addr = address.toString().toUtf8().constData();
    if(old_user.contains(addr)){
        cout <<endl<<"User: "<<old_user.value(addr).data() << " " << "Message: ";
    }
    cout << &buff[4] << endl;
    cout << "Enter message to send: ";
}

void client::user_response(QHostAddress address, char *buff, int rd_cnt){/*Dobija se ime usera*/
    buff[rd_cnt] = '\0';
    QByteArray ip_addr = address.toString().toUtf8().constData();
    QByteArray user_name;
    user_name.clear();
    user_name.append(&buff[5]);
    users[ip_addr] = user_name;
}

void client::reg_response(QHostAddress address){ /*Poziva se nakon datagrama koji sadrzi USRREG, njemu se dodeljuje prefiks USR=*/
    QByteArray data;
    data.clear();
    data.append("USER=");
    data.append(user_name);
    UDPsocket->writeDatagram(data, address, 27000);
}

void client::datagram_types(){

    int rd_cnt = 0;
    char buff[1600];
    QHostAddress address;
    quint16 rec_port = 0;
    quint64 datagram_size;

    while(UDPsocket->hasPendingDatagrams()){ /*Srz programa, cita dobijene datagrame, na osnovu prefiksa se odredjuje sta se dalje radi u programu*/
        datagram_size = UDPsocket->pendingDatagramSize();
        rd_cnt = UDPsocket->readDatagram(buff, datagram_size, &address, &rec_port);
        if(*ip_address == address){
            continue;
        }
        if(0 == strncmp(buff,"USRREG",6)){
            reg_response(address);
        }
        if(0 == strncmp(buff, "USER=", 5)){
            user_response(address, buff, rd_cnt);
        }
        if(0 == strncmp(buff, "MSG=", 4)){
            msg_response(address, buff, rd_cnt);
        }
    }
}


