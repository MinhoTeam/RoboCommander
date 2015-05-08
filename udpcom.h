#ifndef UDPCOM_H
#define UDPCOM_H
#include "mainwindow.h"
#include "QHostAddress"
#include <QUdpSocket>

class UDPCOM
{
public:
    UDPCOM(MainWindow *mainw, QString MyAddress1, QString DestineAddress1, int MyPort1, int DestinePort1,int id);
    ~UDPCOM();
    QString UDPread(void);
    void UDPwrite(QString txt);
private:
    MainWindow *myMain;
    QUdpSocket *udpSocketOut;
    QUdpSocket *udpSocketIn;
    QString MyAddress;
    QString DestineAddress;
    int MyPort,DestinePort;
};

#endif // UDPCOM_H
