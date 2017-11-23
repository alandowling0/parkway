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
    if(!QFile::exists(Database::DATABASE_NAME))
    {
        QFile defaultDatabase(":/database/" + Database::DATABASE_NAME);
        defaultDatabase.copy(Database::DATABASE_NAME);
    }

    QFile database(Database::DATABASE_NAME);
    database.setPermissions(QFile::WriteUser);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto childrenListModel = new ChildrenListModel();
    engine.addImageProvider("childimageprovider", new ChildImageProvider(*childrenListModel));
    engine.rootContext()->setContextProperty(QString("childrenListModel"), childrenListModel);
    engine.rootContext()->setContextProperty(QString("parentsListModel"), new ParentsListModel());
    engine.rootContext()->setContextProperty(QString("timetablesListModel"), new TimetablesListModel());
    engine.rootContext()->setContextProperty(QString("groupsListModel"), new GroupsListModel());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
