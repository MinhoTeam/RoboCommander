#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QStringList readConfigs(QString name);
    void connectUDPS(QStringList lista);
    void readPendingDatagrams1(); //Robo1
    void readPendingDatagrams2(); //Robo2
    void readPendingDatagrams3(); //Robo3
    void readPendingDatagrams4(); //Robo4
    void readPendingDatagrams5(); //Robo5
    void sendRoboData();
    void sendStop();
private:
    Ui::MainWindow *ui;
    bool stop,Up,Down,Left,Right;
    int LinearSpeed,RotationSpeed,Angle;
    QTimer *UDPSenderTimer;
};

#endif // MAINWINDOW_H
