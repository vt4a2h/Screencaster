#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T20:43:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Screencaster
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        MainWindow.cpp \
    Screencaster.cpp

HEADERS  += MainWindow.h \
    Screencaster.h \
    Settings.h

FORMS    += MainWindow.ui

CONFIG += c++14

RESOURCES += \
    main.qrc
