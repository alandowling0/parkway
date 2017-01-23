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

    if(QFile::exists(Database::DATABASE_NAME))
    {
        auto removeOk = QFile::remove(Database::DATABASE_NAME);

        qDebug() << removeOk;
    }
    QFile database(":/database/" + Database::DATABASE_NAME);
    database.copy(Database::DATABASE_NAME);

    QFile copy(Database::DATABASE_NAME);
    copy.setPermissions(QFile::WriteUser);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.addImageProvider("childimageprovider", new ChildImageProvider());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
