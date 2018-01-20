#-------------------------------------------------
#
# Project created by QtCreator 2018-01-01T16:31:53
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetCharts
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    areaseries.cpp \
    barchart.cpp \
    callOut/calloutview.cpp \
    callOut/calloutitem.cpp

HEADERS  += mainwindow.h \
    areaseries.h \
    barchart.h \
    callOut/calloutview.h \
    callOut/calloutitem.h

DESTDIR = $$OUT_PWD/target
MOC_DIR = $$OUT_PWD/tmp/Moc
OBJECTS_DIR = $$OUT_PWD/tmp/Obj
