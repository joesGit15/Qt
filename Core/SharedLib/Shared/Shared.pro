#-------------------------------------------------
#
# Project created by QtCreator 2017-12-04T09:30:37
#
#-------------------------------------------------

QT       -= gui

TARGET = Shared
TEMPLATE = lib

DEFINES += SHARED_LIBRARY

SOURCES += shared.cpp

HEADERS += shared.h\
        shared_global.h

linux {
    CONFIG(debug,debug|release){
        DESTDIR = $$PWD/../_LibOut/Linux/Debug/
    }

    CONFIG(release,debug|release){
        DESTDIR = $$PWD/../_LibOut/Linux/Release/
    }
}

mac {
    CONFIG(debug,debug|release){
        DESTDIR = $$PWD/../_LibOut/Mac/Debug/
    }

    CONFIG(release,debug|release){
        DESTDIR = $$PWD/../_LibOut/Mac/Release/
    }
}

win32 {
    CONFIG(debug,debug|release){
        DESTDIR = $$PWD/../_LibOut/Win/Debug/
    }

    CONFIG(release,debug|release){
        DESTDIR = $$PWD/../_LibOut/Win/Release/
    }
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
