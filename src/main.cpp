#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QFile>
#include "childrenlistmodel.h"
#include "parentslistmodel.h"
#include "timetableslistmodel.h"
#include "groupslistmodel.h"
#include "childimageprovider.h"
#include "database.h"

int main(int argc, char *argv[])
{
    if(!QFile::exists(Database::DATABASE_NAME))
    {
        QFile defaultDatabaseFile(":/database/" + Database::DATABASE_NAME);
        defaultDatabaseFile.copy(Database::DATABASE_NAME);
    }

    QFile databaseFile(Database::DATABASE_NAME);
    databaseFile.setPermissions(QFile::WriteUser);

    QGuiApplication app(argc, argv);

    Database database;
    auto childrenListModel = new ChildrenListModel(database);

    QQmlApplicationEngine engine;
    engine.addImageProvider("childimageprovider", new ChildImageProvider(*childrenListModel));
    engine.rootContext()->setContextProperty(QString("childrenListModel"), childrenListModel);
    engine.rootContext()->setContextProperty(QString("parentsListModel"), new ParentsListModel(database));
    engine.rootContext()->setContextProperty(QString("parentsOfChildListModel"), new ParentsListModel(database));
    engine.rootContext()->setContextProperty(QString("timetablesListModel"), new TimetablesListModel(database));
    engine.rootContext()->setContextProperty(QString("groupsListModel"), new GroupsListModel(database));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
