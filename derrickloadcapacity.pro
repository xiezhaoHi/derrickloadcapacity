#-------------------------------------------------
#
# Project created by QtCreator 2017-04-04T17:11:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = derrickloadcapacity
TEMPLATE = app
#CONFIG += console

SOURCES += main.cpp\
        sderrickloadcapacitymainwin.cpp \
    sdatabasemanager.cpp \
    salgo.cpp

HEADERS  += sderrickloadcapacitymainwin.h \
    sdatabasemanager.h \
    salgo.h

FORMS    += sderrickloadcapacitymainwin.ui
