greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS = \
    mainwindow.h \
    optionsdialog.h \
    searchdialog.h

SOURCES = \
    main.cpp \
    mainwindow.cpp \
    optionsdialog.cpp \
    searchdialog.cpp

RESOURCES = \
    qhexedit.qrc

FORMS += \
    optionsdialog.ui \
    searchdialog.ui

TRANSLATIONS += \
    translations/qhexedit_cs.ts \
    translations/qhexedit_de.ts

DEFINES += QHEXEDIT_EXPORTS

INCLUDEPATH += $$PWD/../lib/include

linux:CONFIG(debug,debug|release) {
    LIBS += -L$$PWD/../lib/linux/debug -lQHexEdit
}

linux:CONFIG(release,release|release) {
    LIBS += -L$$PWD/../lib/linux/release -lQHexEdit
}

win32:CONFIG(debug,debug|release) {
    LIBS += -L$$PWD/../lib/win32/debug -lQHexEdit
}

win32:CONFIG(release,release|release) {
    LIBS += -L$$PWD/../lib/win32/release -lQHexEdit
}
