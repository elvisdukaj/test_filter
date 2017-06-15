#include "thresholdfilter.h"
#include "cannyfilter.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
	
	qmlRegisterType<ThresholdFilter>("qubicaamf.vision", 1, 0, "ThresholdFilter");
    qmlRegisterType<CannyFilter>("qubicaamf.vision", 1, 0, "CannyFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
