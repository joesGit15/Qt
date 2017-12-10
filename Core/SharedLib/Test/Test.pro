QT += core
QT -= gui

CONFIG += c++11

TARGET = Test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += $$PWD/../Shared/

linux {
    CONFIG(debug,debug|release){
        LIBS += -L$$PWD/../_LibOut/Linux/Debug -lShared
    }
    CONFIG(release,debug|release){
        LIBS += -L$$PWD/../_LibOut/Linux/Release -lShared
    }
}

mac {
    CONFIG(debug,debug|release){
        LIBS += -L$$PWD/../_LibOut/Mac/Debug -lShared
    }
    CONFIG(release,debug|release){
        LIBS += -L$$PWD/../_LibOut/Mac/Release -lShared
    }
}

win32 {
    CONFIG(debug,debug|release){
        LIBS += -L$$PWD/../_LibOut/Win/Debug -lShared
    }
    CONFIG(release,debug|release){
        LIBS += -L$$PWD/../_LibOut/Win/Release -lShared
    }
}
