
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += core gui
TEMPLATE = lib

VERSION = 4.0.0

DEFINES += QHEXEDIT_EXPORTS

HEADERS = \
    commands.h \
    chunks.h \
    qhexedit.h

SOURCES = \
    qhexedit.cpp \
    chunks.cpp \
    commands.cpp

Release:TARGET = qhexedit
Debug:TARGET = qhexeditd

linux:CONFIG(debug,debug|release) {
    DESTDIR = $$PWD/../lib/linux/debug
}

linux:CONFIG(release,debug|release) {
    DESTDIR = $$PWD/../lib/linux/release
}

linux{
    system(cp -f $$PWD/*.h $$PWD/../lib/include)
}


win32:CONFIG(debug,debug|release) {
    DESTDIR = $$PWD/../lib/win32/debug
}

win32:CONFIG(release,debug|release) {
    DESTDIR = $$PWD/../lib/win32/release
}

win32{
    system(copy /Y $$PWD/*.h $$PWD/../lib/include)
}
