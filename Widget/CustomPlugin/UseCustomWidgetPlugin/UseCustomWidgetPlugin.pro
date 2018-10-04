#-------------------------------------------------
#
# Project created by QtCreator 2018-10-04T19:07:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UseCustomWidgetPlugin
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

LIBS += -L$$[QT_INSTALL_PLUGINS]/designer -lcustomwidgetplugin
