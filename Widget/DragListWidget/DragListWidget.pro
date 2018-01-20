#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T09:24:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DragListWidget
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    draglistitemdelegate.cpp \
    draglistwidget.cpp

HEADERS  += dialog.h \
    draglistitemdelegate.h \
    draglistwidget.h

FORMS    += dialog.ui
