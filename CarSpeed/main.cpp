#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qdatamgr.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QDataMgr data_mgr;
    engine.rootContext()->setContextProperty("DATAMGR", &data_mgr);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
