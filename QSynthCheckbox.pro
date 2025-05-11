#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T12:09:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../SynthPanel/QSynthPanel.pri)
include(QSynthCheckbox.pri)

TARGET = QSynthCheckbox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

