#-------------------------------------------------
#
# Project created by QtCreator 2017-09-09T10:18:07
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditorFactory
TEMPLATE = app
VERSION = 00.00.01

CONFIG(debug,debug|release){

}else{

}

linux {
    DESTDIR = $$OUT_PWD/target
    MOC_DIR = $$OUT_PWD/tmp/Moc
    OBJECTS_DIR = $$OUT_PWD/tmp/Obj
}

SOURCES += \
    editorfactorwidget.cpp \
    colorlisteditor.cpp \
    coloritemdelegate.cpp \
    main.cpp

HEADERS  += \
    editorfactorwidget.h \
    colorlisteditor.h \
    coloritemdelegate.h
