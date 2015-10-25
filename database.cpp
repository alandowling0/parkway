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

std::vector<Parent> Database::GetParents(std::string const& childName)
{
    std::vector<Parent> parents;

    QSqlQuery child(iSqliteDatabase);
    child.prepare("SELECT id FROM Children WHERE name=?");
    child.addBindValue(childName.c_str());
    if(!child.exec())
        qDebug() << child.lastError().text();

    while(child.next())
    {
        auto childId = child.value(0);

        QSqlQuery relation(iSqliteDatabase);
        relation.prepare("SELECT parent FROM Relations WHERE child=?");
        relation.addBindValue(childId);

        if(!relation.exec())
            qDebug() << relation.lastError().text();

        while(relation.next())
        {
            auto parentId = relation.value(0);

            QSqlQuery parent(iSqliteDatabase);
            parent.prepare("SELECT Parents.name, Parents.email, Parents.phone "
                           "FROM Parents "
                           "WHERE Parents.id=?");
            parent.addBindValue(parentId);

            if(!parent.exec())
                qDebug() << parent.lastError().text();

            while(parent.next())
            {
                auto name = parent.value(0).toString();
                auto email = parent.value(1).toString();
                auto phone = parent.value(2).toString();

                parents.emplace_back(name, email, phone);
            }
        }
    }

    return parents;
}
