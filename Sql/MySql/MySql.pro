#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T21:02:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySql
TEMPLATE = app

linux {
    DESTDIR = $$OUT_PWD/target
    MOC_DIR = $$OUT_PWD/tmp/Moc
    OBJECTS_DIR = $$OUT_PWD/tmp/Obj
}

SOURCES += main.cpp\
    mainwindow.cpp \
    DatabaseConnect.cpp

HEADERS  += \
    mainwindow.h \
    DatabaseConnect.h
