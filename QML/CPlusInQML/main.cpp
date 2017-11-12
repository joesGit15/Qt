/**
  @brief: How to use c++ in QML
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#if 0
#include <QtQml/qqmlcontext.h>
#endif

#include "colormaker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ColorMaker>("joe.qt.ColorMaker",1,0,"ColorMaker");

    QQmlApplicationEngine engine;
#if 0
    engine.rootContext()->setContextProperty("id_colorMaker",new ColorMaker);
#endif
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
