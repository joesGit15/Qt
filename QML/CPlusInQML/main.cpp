/**
  @brief: How to use c++ in QML
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "colormaker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ColorMaker>("joe.qt.ColorMaker",1,0,"ColorMaker");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
