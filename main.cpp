#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "childrenlistmodel.h"
#include "parentslistmodel.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<ChildrenListModel>("com.panchito.parkway", 1, 0, "ChildrenListModel");
    qmlRegisterType<ParentsListModel>("com.panchito.parkway", 1, 0, "ParentsListModel");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
