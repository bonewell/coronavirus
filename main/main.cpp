#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "regularpolygonmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    RegularPolygonModel model;
    model.addPolygon({{250, 250}, 200, 7});
    engine.rootContext()->setContextProperty("polygons", &model);

    return app.exec();
}
