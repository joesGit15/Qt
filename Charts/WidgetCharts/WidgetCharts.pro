#-------------------------------------------------
#
# Project created by QtCreator 2018-01-01T16:31:53
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetCharts
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    areaSeries/areaseries.cpp \
    barChart/barchart.cpp \
    callOut/calloutview.cpp \
    callOut/calloutitem.cpp \
    chartInteractions/interactionchart.cpp \
    chartInteractions/interactionchartview.cpp \
    chartInteractions/interactionwidget.cpp \
    chartThemes/themewidget.cpp \
    customChart/customchartwidget.cpp \
    barChart/barchartwidget.cpp \
    barChart/horizontalbarchart.cpp \
    barChart/horizontalpercentbarchart.cpp \
    barChart/horizontalstackedbarchart.cpp \
    dynamicspline/dynamicsplinewidget.cpp \
    legend/legend.cpp \
    legendmarkers/legendmarkerswidget.cpp \
    barChart/lineandbar.cpp \
    logvalueaxis/logvalueaxis.cpp \
    multiaxis/multiaxis.cpp \
    openglseries/openglseries.cpp \
    openglseries/datasource.cpp \
    piechart/donutbreakdown/donutbreakdownchart.cpp \
    piechart/donutbreakdown/donutbreakdownwidget.cpp \
    piechart/donutbreakdown/mainslice.cpp \
    piechart/donutchart/donutchartwidget.cpp \
    piechart/piechart.cpp \
    piechart/piechartdrilldown/drilldownchart.cpp \
    piechart/piechartdrilldown/drilldownslice.cpp \
    piechart/piechartdrilldown/drilldownwidget.cpp \
    piechart/piechartcustomization/brushtool.cpp \
    piechart/piechartcustomization/customslice.cpp \
    piechart/piechartcustomization/pentool.cpp \
    piechart/piechartcustomization/piechartcustomization.cpp \
    piechart/nesteddonuts/nesteddonuts.cpp \
    scatter/scatter.cpp \
    scatter/scatterchart/scatterchart.cpp \
    scatter/scatterinteractions/scatterinteractions.cpp \
    barChart/stackedbarchartdrilldown/stackedbardrilldown.cpp \
    barChart/stackedbarchartdrilldown/bardrilldownchart.cpp \
    barChart/stackedbarchartdrilldown/drilldownseries.cpp \
    barChart/temperaturerecords/temperaturerecords.cpp

HEADERS  += mainwindow.h \
    areaSeries/areaseries.h \
    barChart/barchart.h \
    callOut/calloutview.h \
    callOut/calloutitem.h \
    chartInteractions/interactionchart.h \
    chartInteractions/interactionchartview.h \
    chartInteractions/interactionwidget.h \
    chartThemes/themewidget.h \
    customChart/customchartwidget.h \
    barChart/barchartwidget.h \
    barChart/horizontalbarchart.h \
    barChart/horizontalpercentbarchart.h \
    barChart/horizontalstackedbarchart.h \
    dynamicspline/dynamicsplinewidget.h \
    legend/legend.h \
    legendmarkers/legendmarkerswidget.h \
    barChart/lineandbar.h \
    logvalueaxis/logvalueaxis.h \
    multiaxis/multiaxis.h \
    openglseries/openglseries.h \
    openglseries/datasource.h \
    piechart/donutbreakdown/donutbreakdownchart.h \
    piechart/donutbreakdown/donutbreakdownwidget.h \
    piechart/donutbreakdown/mainslice.h \
    piechart/donutchart/donutchartwidget.h \
    piechart/piechart.h \
    piechart/piechartdrilldown/drilldownchart.h \
    piechart/piechartdrilldown/drilldownslice.h \
    piechart/piechartdrilldown/drilldownwidget.h \
    piechart/piechartcustomization/brushtool.h \
    piechart/piechartcustomization/customslice.h \
    piechart/piechartcustomization/pentool.h \
    piechart/piechartcustomization/piechartcustomization.h \
    piechart/nesteddonuts/nesteddonuts.h \
    scatter/scatter.h \
    scatter/scatterchart/scatterchart.h \
    scatter/scatterinteractions/scatterinteractions.h \
    barChart/stackedbarchartdrilldown/stackedbardrilldown.h \
    barChart/stackedbarchartdrilldown/bardrilldownchart.h \
    barChart/stackedbarchartdrilldown/drilldownseries.h \
    barChart/temperaturerecords/temperaturerecords.h

DESTDIR = $$OUT_PWD/target
MOC_DIR = $$OUT_PWD/tmp/Moc
OBJECTS_DIR = $$OUT_PWD/tmp/Obj

FORMS +=
