#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QFile>
#include "childrenlistmodel.h"
#include "parentslistmodel.h"
#include "timetableslistmodel.h"
#include "groupslistmodel.h"
#include "childimageprovider.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<ChildrenListModel>("com.panchito.parkway", 1, 0, "ChildrenListModel");
    qmlRegisterType<ParentsListModel>("com.panchito.parkway", 1, 0, "ParentsListModel");
    qmlRegisterType<TimetablesListModel>("com.panchito.parkway", 1, 0, "TimetablesListModel");
    qmlRegisterType<GroupsListModel>("com.panchito.parkway", 1, 0, "GroupsListModel");

    if(QFile::exists("parkway.db"))
    {
        auto removeOk = QFile::remove("parkway.db");

        qDebug() << removeOk;
    }
    QFile database(":/database/parkway.db");
    database.copy("parkway.db");

    QFile copy("parkway.db");
    copy.setPermissions(QFile::WriteUser);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.addImageProvider("childimageprovider", new ChildImageProvider());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
