#include "udpcom.h"

UDPCOM::UDPCOM(MainWindow *mainw, QString MyAddress1, QString DestineAddress1, int MyPort1, int DestinePort1, int id)
{
    MyAddress = MyAddress1;
    DestineAddress = DestineAddress1;
    DestinePort = DestinePort1;
    MyPort = MyPort1;

    myMain = mainw;
    udpSocketOut = new QUdpSocket(mainw);
    udpSocketOut->bind(QHostAddress(DestineAddress), DestinePort);

    udpSocketIn = new QUdpSocket(mainw);
    udpSocketIn->bind(QHostAddress(MyAddress), MyPort);
    if(id == 0)
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams0()));
    else if(id == 1)
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams1()));
    else if(id == 2)
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams2()));
    else if(id == 3)
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams3()));
    else if(id == 4)
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams4()));
    else if(id == 5)
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams5()));

}

UDPCOM::~UDPCOM()
{
    udpSocketOut->close();
    udpSocketIn->close();
}

QString UDPCOM::UDPread()
{
    QString lido;
    while (udpSocketIn->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketIn->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketIn->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        lido += datagram;
    }
    return lido;
}

void UDPCOM::UDPwrite(QString txt)
{
    QByteArray datagram;
    datagram.append(txt);
    udpSocketOut->writeDatagram(datagram,QHostAddress(DestineAddress), DestinePort);
}

