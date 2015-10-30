#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "childrenlistmodel.h"
#include "parentslistmodel.h"
#include "timetableslistmodel.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<ChildrenListModel>("com.panchito.parkway", 1, 0, "ChildrenListModel");
    qmlRegisterType<ParentsListModel>("com.panchito.parkway", 1, 0, "ParentsListModel");
    qmlRegisterType<TimetablesListModel>("com.panchito.parkway", 1, 0, "TimetablesListModel");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
