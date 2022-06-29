#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "game.h"
#include "polygonfactory.h"
#include "regularpolygonmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("CoronaVirus");
    QGuiApplication::setApplicationVersion("1.0");

#ifndef Q_OS_WASM
    QCommandLineParser parser;
    parser.setApplicationDescription("Simulates live of the viruses");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"q", "quantity"}, "Quantity of the polygons on start. Default is 1", "quantity", "1"},
        {{"r", "radius"}, "Size of the polygon in pixels. Default is 50", "radius", "50"},
        {{"l", "lifetime"}, "Lifetime of the polygon in seconds. Default is 10", "lifetime", "10"},
    });
    parser.addPositionalArgument("min", "Minimum number of the sides of the polygon");
    parser.addPositionalArgument("max", "Maximum number of the sides of the polygon");
    parser.process(app);

    auto quantity = parser.value("quantity").toInt();
    auto radius = parser.value("radius").toDouble();
    auto lifetime = parser.value("lifetime").toInt() * 1000;
    auto strings = parser.positionalArguments();

    if (strings.length() < 2) qFatal("min and max should be specified");
    auto limits = std::make_pair<int, int>(strings.at(0).toInt(), strings.at(1).toInt());

    if (limits.first < 3) qFatal("min should be greater 3");
    if (limits.first > limits.second) qFatal("min should be less max");
#else
    int quantity = 1;
    qreal radius = 50;
    int lifetime = 5 * 1000;
    auto limits = std::make_pair(3, 5);
#endif  // Q_OS_WASM

    qDebug() << "quantity=" << quantity;
    qDebug() << "radius=" << radius;
    qDebug() << "lifetime=" << lifetime;
    qDebug() << "min=" << limits.first;
    qDebug() << "max=" << limits.second;

    PolygonFactory factory{lifetime, radius, limits};
    RegularPolygonModel model;
    Game game{quantity, factory, model};

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, QUrl const& objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &game, [&game](QObject* object, QUrl const&) {
        auto window = qobject_cast<QQuickWindow*>(object);
        QObject::connect(window, &QQuickWindow::heightChanged,
                         window, [&game, window] (int) {
            game.setSize(window->size());
        });
        QObject::connect(window, &QQuickWindow::widthChanged,
                         window, [&game, window] (int) {
            game.setSize(window->size());
        });
    });
    engine.rootContext()->setContextProperty("polygons", &model);
    engine.load(url);

    return app.exec();
}
