#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T22:01:22
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoboUDPCommander
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udpcom.cpp

HEADERS  += mainwindow.h \
    udpcom.h

FORMS    += mainwindow.ui

RESOURCES += \
    rs.qrc
