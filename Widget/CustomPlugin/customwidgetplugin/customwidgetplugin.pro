QT          += widgets uiplugin
CONFIG      += plugin
TEMPLATE    = lib

#message($$qtLibraryTarget) #Project MESSAGE:
#message($$TARGET) #customwidgetplugin

#TARGET = $$qtLibraryTarget($$TARGET)

HEADERS     = customwidgetplugin.h
SOURCES     = customwidgetplugin.cpp

include(customwidget.pri)
