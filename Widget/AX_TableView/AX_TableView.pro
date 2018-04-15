#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T16:38:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AX_TableView
TEMPLATE = app

SOURCES += main.cpp\
        ax_widget.cpp \
    ax_tablemodel.cpp \
    ax_styleitemdelegate.cpp

HEADERS  += ax_widget.h \
    ax_tablemodel.h \
    ax_styleitemdelegate.h

RESOURCES += \
    res.qrc
