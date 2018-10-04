#include "analogclock.h"
#include "customwidgetplugin.h"

#include <QtPlugin>

AnalogClockPlugin::AnalogClockPlugin(QObject *parent)
    : QObject(parent)
    , initialized(false)
{
}

void AnalogClockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool AnalogClockPlugin::isInitialized() const
{
    return initialized;
}

QWidget *AnalogClockPlugin::createWidget(QWidget *parent)
{
    return new AnalogClock(parent);
}

QString AnalogClockPlugin::name() const
{
    return "AnalogClock";
}

QString AnalogClockPlugin::group() const
{
    return "Display Widgets [Examples]";
}

QIcon AnalogClockPlugin::icon() const
{
    return QIcon();
}

QString AnalogClockPlugin::toolTip() const
{
    return "";
}

QString AnalogClockPlugin::whatsThis() const
{
    return "";
}

bool AnalogClockPlugin::isContainer() const
{
    return false;
}

QString AnalogClockPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"AnalogClock\" name=\"analogClock\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>The current time</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>The analog clock widget displays the current time.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString AnalogClockPlugin::includeFile() const
{
    return "analogclock.h";
}
