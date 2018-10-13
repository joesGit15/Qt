#-------------------------------------------------
#
# Project created by QtCreator 2018-09-11T13:53:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenProcess
TEMPLATE = app

SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h

!win32{
    error("must be win32 os")
}
