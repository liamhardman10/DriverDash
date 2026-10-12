#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Identify the app to the desktop environment / window manager.
    QGuiApplication::setApplicationName("DriverDash");
    QGuiApplication::setOrganizationName("DriverDash");
    QGuiApplication::setApplicationVersion("0.1.0");

    // AppController is the C++ side of the bridge.
    // We expose it as a context property named "app" so QML can reach it.
    AppController controller;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app", &controller);

    // Load Main.qml from the QML module we defined in CMakeLists.
    // The path is qrc:/qt/qml/<URI>/<path-inside-module>.
    const QUrl url(QStringLiteral("qrc:/qt/qml/DriverDash/qml/Main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) {
                qCritical("Failed to load %s", qPrintable(url.toString()));
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}