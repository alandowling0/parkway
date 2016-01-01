#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "childrenlistmodel.h"
#include "parentslistmodel.h"
#include "timetableslistmodel.h"
#include "groupslistmodel.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<ChildrenListModel>("com.panchito.parkway", 1, 0, "ChildrenListModel");
    qmlRegisterType<ParentsListModel>("com.panchito.parkway", 1, 0, "ParentsListModel");
    qmlRegisterType<TimetablesListModel>("com.panchito.parkway", 1, 0, "TimetablesListModel");
    qmlRegisterType<GroupsListModel>("com.panchito.parkway", 1, 0, "GroupsListModel");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
