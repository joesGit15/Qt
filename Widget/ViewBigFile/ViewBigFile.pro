#-------------------------------------------------
#
# Project created by QtCreator 2018-10-01T16:17:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewBigFile
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    GenerateBigFile/generatebigfilewgt.cpp \
    ViewBigFile/viewbigfilewgt.cpp

HEADERS  += dialog.h \
    GenerateBigFile/generatebigfilewgt.h \
    ViewBigFile/viewbigfilewgt.h
