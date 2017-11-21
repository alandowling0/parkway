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
    engine.rootContext()->setContextProperty(QString("childrenListModel"), new ChildrenListModel());
    engine.rootContext()->setContextProperty(QString("parentsListModel"), new ParentsListModel());
    engine.rootContext()->setContextProperty(QString("timetablesListModel"), new TimetablesListModel());
    engine.rootContext()->setContextProperty(QString("groupsListModel"), new GroupsListModel());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
