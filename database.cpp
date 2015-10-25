#include "database.h"
#include <cassert>

Database::Database()
{
    auto names = QSqlDatabase::connectionNames();
    auto count = names.size();
    iConnectionName = QString(std::to_string(count).c_str());
    iSqliteDatabase = QSqlDatabase::addDatabase("QSQLITE", iConnectionName);
    iSqliteDatabase.setDatabaseName("..\\parkway\\database\\parkway.db");

    bool open = iSqliteDatabase.open();
    if(!open)
    {
       qDebug() << iSqliteDatabase.lastError().text();
       assert(open);
    }

    QSqlQuery query(iSqliteDatabase);
    query.prepare("PRAGMA foreign_keys = ON;");
    if(!query.exec())
        qDebug() << query.lastError().text();
}

Database::~Database()
{
    iSqliteDatabase.close();
    QSqlDatabase::removeDatabase(iConnectionName);
}

std::vector<Child> Database::GetAllChildren()
{
    std::vector<Child> children;

    QSqlQuery query(iSqliteDatabase);

    query.prepare("SELECT Children.name, Children.image, Groups.name "
                  "FROM Children "
                  "INNER JOIN Groups "
                  "ON Children.\"group\"=Groups.id");

    if(!query.exec())
        qDebug() << query.lastError().text();

    while(query.next())
    {
        auto name = query.value(0).toString();
        auto image = query.value(1).toString();
        auto group = query.value(2).toString();

        children.emplace_back(name, image, group);
    }

    return children;
}

std::vector<Parent> Database::GetAllParents()
{
    std::vector<Parent> parents;

    QSqlQuery query(iSqliteDatabase);

    query.prepare("SELECT Parents.name, Parents.email, Parents.phone "
                  "FROM Parents ");

    if(!query.exec())
        qDebug() << query.lastError().text();

    while(query.next())
    {
        auto name = query.value(0).toString();
        auto email = query.value(1).toString();
        auto phone = query.value(2).toString();

        parents.emplace_back(name, email, phone);
    }

    return parents;
}
