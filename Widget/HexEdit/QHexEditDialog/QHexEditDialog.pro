greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS = \
    optionsdialog.h \
    ../QHexEdit/qhexedit.h \
    ../QHexEdit/chunks.h \
    ../QHexEdit/commands.h \
    searchdialog.h \
    qhexeditdialog.h


SOURCES = \
    main.cpp \
    optionsdialog.cpp \
    ../QHexEdit/qhexedit.cpp \
    ../QHexEdit/chunks.cpp \
    ../QHexEdit/commands.cpp \
    searchdialog.cpp \
    qhexeditdialog.cpp

RESOURCES = \
    qhexedit.qrc

FORMS += \
    optionsdialog.ui \
    searchdialog.ui

TRANSLATIONS += \
    translations/qhexedit_cs.ts \
    translations/qhexedit_de.ts

DEFINES += QHEXEDIT_EXPORTS
