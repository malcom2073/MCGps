QT += core serialport
QT -= gui

CONFIG += c++11

TARGET = MCGpsProvider
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mcgpsprovider.cpp \
    nmeadatasource.cpp

HEADERS += \
    mcgpsprovider.h \
    nmeadatasource.h


include(../MCIPC/MCIPC.pri)
