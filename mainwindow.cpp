#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpcom.h"

UDPCOM *UDP[6];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stop = true;
    LinearSpeed = 0;
    RotationSpeed=0;
    Angle=0;
    Up=false;Down=false;Left=false;Right=false;

    QStringList lines;
    lines = readConfigs("configs.txt");
    if(lines.length()==16)
    {
        connectUDPS(lines);
    }
    else QMessageBox::information(this,"Error: ","Configs txt not OK!: "+QString::number(lines.length()));

    UDPSenderTimer = new QTimer();
    connect(UDPSenderTimer,SIGNAL(timeout()),this,SLOT(sendRoboData()));
    UDPSenderTimer->start(100);//10fps
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key())
    {
        case Qt::Key_Right:
        if(Up) Angle=315;
        else if(Down) Angle=225;
        else Angle=270;
        Right=true;
        ui->lbAngle->setText("Directional Angle: "+QString::number(Angle)+"º");
        break;
        case Qt::Key_Left:
        if(Up) Angle=45;
        else if(Down) Angle=135;
        else Angle=90;
        Left=true;
        ui->lbAngle->setText("Directional Angle: "+QString::number(Angle)+"º");
        break;
        case Qt::Key_Up:
        if(Right) Angle=315;
        else if(Left) Angle=45;
        else Angle=0;
        Up=true;
        ui->lbAngle->setText("Directional Angle: "+QString::number(Angle)+"º");
        break;
        case Qt::Key_Down:
        if(Right) Angle=225;
        else if(Left) Angle=135;
        else Angle=180;
        Down=true;
        ui->lbAngle->setText("Directional Angle: "+QString::number(Angle)+"º");
        break;


        case Qt::Key_Alt:
        ui->lbState->setText("State: Run");
        stop=false;
        break;


        case Qt::Key_W:
        if(LinearSpeed<100) LinearSpeed++;
        ui->lbLinearSpeed->setText("LinearSpeed: "+QString::number(LinearSpeed));
        break;
        case Qt::Key_S:
        if(LinearSpeed>0) LinearSpeed--;
        ui->lbLinearSpeed->setText("LinearSpeed: "+QString::number(LinearSpeed));
        break;
        case Qt::Key_D:
        if(RotationSpeed<100)
        RotationSpeed++;
        ui->lbRotational->setText("Rotational Speed: : "+QString::number(RotationSpeed)+" º");
        break;
        case Qt::Key_A:
        if(RotationSpeed>-100)
        RotationSpeed--;
        ui->lbRotational->setText("Rotational Speed: : "+QString::number(RotationSpeed)+" º");
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key())
    {
        case Qt::Key_Right:
        Right=false;
        break;
        case Qt::Key_Left:
        Left=false;
        break;
        case Qt::Key_Up:
        Up=false;
        break;
        case Qt::Key_Down:
        Down=false;
        break;

        case Qt::Key_Alt:
        sendStop();
        ui->lbState->setText("State: Stop");
        stop=true;
        break;

    }
}

QStringList MainWindow::readConfigs(QString name)
{
    QFile file(name);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        QStringList listFail;
        return listFail;
    }
    else{
        QTextStream in(&file);
        QStringList lines;
        while(!in.atEnd()) {
            QString lido = in.readLine();
            lido = lido.remove(lido.indexOf("#"),lido.length());
            qDebug() << lido;
            lines.append(lido);
        }
        file.close();
        return lines;
    }

}

void MainWindow::readPendingDatagrams1()
{
    QString lido = UDP[1]->UDPread();
}

void MainWindow::readPendingDatagrams2()
{
    QString lido = UDP[2]->UDPread();
}

void MainWindow::readPendingDatagrams3()
{
    QString lido = UDP[3]->UDPread();
}

void MainWindow::readPendingDatagrams4()
{
    QString lido = UDP[4]->UDPread();
}

void MainWindow::readPendingDatagrams5()
{
    QString lido = UDP[5]->UDPread();
}

void MainWindow::connectUDPS(QStringList lista)
{
    //////////////////Abrir Sockets UDP para os 5 Robos/////////////////////////////
    try
    {
        //MyAddress,DestinationAddress,MyPort,DestinationPort
        UDP[1] = new UDPCOM(this,lista.at(0),lista.at(1),lista.at(3).toInt(),lista.at(2).toInt(),1);
        //UDP[1] = new UDPCOM(this,"172.16.49.50","172.16.49.2",2221,1111,1);
    }
    catch(...)
    {
        QMessageBox::information(this,"Error","Could not creat socket to robot1");
    }
    ///////////////////////////////////////////////////////////////////////////////
    try
    {
        //MyAddress,DestinationAddress,MyPort,DestinationPort
        UDP[2] = new UDPCOM(this,lista.at(0),lista.at(4),lista.at(6).toInt(),lista.at(5).toInt(),2);
    }
    catch(...)
    {
        QMessageBox::information(this,"Error","Could not creat socket to robot2");
    }
    ///////////////////////////////////////////////////////////////////////////////
    try
    {
        //MyAddress,DestinationAddress,MyPort,DestinationPort
        UDP[3] = new UDPCOM(this,lista.at(0),lista.at(7),lista.at(9).toInt(),lista.at(8).toInt(),3);
    }
    catch(...)
    {
        QMessageBox::information(this,"Error","Could not creat socket to robot3");
    }
    ///////////////////////////////////////////////////////////////////////////////
    try
    {
        //MyAddress,DestinationAddress,MyPort,DestinationPort
        UDP[4] = new UDPCOM(this,lista.at(0),lista.at(10),lista.at(12).toInt(),lista.at(11).toInt(),4);
    }
    catch(...)
    {
        QMessageBox::information(this,"Error","Could not creat socket to robot4");
    }
    ///////////////////////////////////////////////////////////////////////////////
    try
    {
        //MyAddress,DestinationAddress,MyPort,DestinationPort
        UDP[5] = new UDPCOM(this,lista.at(0),lista.at(13),lista.at(15).toInt(),lista.at(14).toInt(),5);
    }
    catch(...)
    {
        QMessageBox::information(this,"Error","Could not creat socket to robot5");
    }
    ///////////////////////////////////////////////////////////////////////////////
}

void MainWindow::sendRoboData()
{
    QString data = (":"+QString::number(LinearSpeed)+","+QString::number(RotationSpeed)+","+QString::number(Angle)+",0,0,0,0,0,0\n");
    if(ui->checkBoxRobo1->isChecked() && !stop){
        UDP[1]->UDPwrite(data);
        qDebug() << "Sending1: "<< data;
    }
    if(ui->checkBoxRobo2->isChecked() && !stop){
        UDP[2]->UDPwrite(data);
        qDebug() << "Sending2: "<< data;
    }
    if(ui->checkBoxRobo3->isChecked() && !stop){
        UDP[3]->UDPwrite(data);
        qDebug() << "Sending3: "<< data;
    }
    if(ui->checkBoxRobo4->isChecked() && !stop){
        UDP[4]->UDPwrite(data);
        qDebug() << "Sending4: "<< data;
    }
    if(ui->checkBoxRobo5->isChecked() && !stop){
        UDP[5]->UDPwrite(data);
        qDebug() << "Sending5: "<< data;
    }
}

void MainWindow::sendStop()
{
    QString data = (":0,0,0,0,0,0,0,0,0\n");
    if(ui->checkBoxRobo1->isChecked()){
        UDP[1]->UDPwrite(data);
        qDebug() << "Stop Robot1";
        UDP[1]->UDPwrite(data);
    }
    if(ui->checkBoxRobo2->isChecked()){
        UDP[2]->UDPwrite(data);
        qDebug() << "Stop Robot2";
        UDP[2]->UDPwrite(data);
    }
    if(ui->checkBoxRobo3->isChecked()){
        UDP[3]->UDPwrite(data);
        qDebug() << "Stop Robot3";
        UDP[3]->UDPwrite(data);
    }
    if(ui->checkBoxRobo4->isChecked()){
        UDP[4]->UDPwrite(data);
        qDebug() << "Stop Robot4";
        UDP[4]->UDPwrite(data);
    }
    if(ui->checkBoxRobo5->isChecked()){
        UDP[5]->UDPwrite(data);
        qDebug() << "Stop Robot5";
        UDP[5]->UDPwrite(data);
    }
}
