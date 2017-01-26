#include "database.h"
#include <cassert>

const QString Database::DATABASE_NAME = "parkway.db";

Database::Database()
{
    auto names = QSqlDatabase::connectionNames();
    auto count = names.size();
    iConnectionName = QString(std::to_string(count).c_str());
    iSqliteDatabase = QSqlDatabase::addDatabase("QSQLITE", iConnectionName);
    iSqliteDatabase.setDatabaseName(DATABASE_NAME);

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

std::vector<Child> Database::GetAllChildren() const
{
    std::vector<Child> children;

    QSqlQuery query(iSqliteDatabase);

    query.prepare("SELECT Children.name, Children.dob, Groups.name "
                  "FROM Children "
                  "INNER JOIN Groups "
                  "ON Children.\"group\"=Groups.id");

    if(!query.exec())
        qDebug() << query.lastError().text();

    while(query.next())
    {
        auto name = query.value(0).toString();
        auto dob = query.value(1).toString();
        auto group = query.value(2).toString();

        children.emplace_back(name, dob, group);
    }

    return children;
}

std::vector<Parent> Database::GetAllParents() const
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

std::vector<std::string> Database::GetAllGroups() const
{
    std::vector<std::string> groups;

    QSqlQuery query(iSqliteDatabase);

    query.prepare("SELECT Groups.name "
                  "FROM Groups ");

    if(!query.exec())
        qDebug() << query.lastError().text();

    while(query.next())
    {
        auto name = query.value(0).toString().toStdString();

        groups.emplace_back(name);
    }

    return groups;
}

std::vector<Parent> Database::GetParents(std::string const& childName) const
{
    std::vector<Parent> parents;

    auto childId = ChildId(childName);

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

    return parents;
}


std::vector<Timetable> Database::GetTimetables(std::string const& childName) const
{
    std::vector<Timetable> timetables;

    auto childId = ChildId(childName);

    QSqlQuery timetable(iSqliteDatabase);
    timetable.prepare("SELECT term, monday, tuesday, wednesday, thursday, friday "
                      "FROM Timetables WHERE child=?");
    timetable.addBindValue(childId);

    if(!timetable.exec())
        qDebug() << timetable.lastError().text();

    while(timetable.next())
    {
        auto term = timetable.value(0).toString();
        auto mon = timetable.value(1).toBool();
        auto tue = timetable.value(2).toBool();
        auto wed = timetable.value(3).toBool();
        auto thu = timetable.value(4).toBool();
        auto fri = timetable.value(5).toBool();

        timetables.emplace_back(QString(childName.c_str()), term, mon, tue, wed, thu, fri);
    }

    return timetables;
}

QByteArray Database::GetImageData(std::string const& childName) const
{
    QByteArray data;

    auto childId = ChildId(childName);

    QSqlQuery query(iSqliteDatabase);
    query.prepare("SELECT imageData FROM Children WHERE id=?");
    query.addBindValue(childId);

    auto queryOk = query.exec() && query.first();
    if(queryOk)
    {
        data = query.value(0).toByteArray();
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return data;
}

void Database::AddChild(Child const& child)
{
    auto groupId = GroupId(child.Group().toStdString());

    QSqlQuery query(iSqliteDatabase);
    query.prepare("INSERT INTO Children (name, dob, \"group\") "
                  "VALUES (?, ?, ?)");
    query.addBindValue(child.Name());
    query.addBindValue(child.DateOfBirth());
    query.addBindValue(groupId);

    query.exec();
}

int Database::ChildId(std::string const& childName) const
{
    QSqlQuery childId(iSqliteDatabase);
    childId.prepare("SELECT id FROM Children WHERE name=?");
    childId.addBindValue(childName.c_str());
    if(!childId.exec())
        qDebug() << childId.lastError().text();

    if(childId.first())
    {
        return childId.value(0).toInt();
    }
    else
    {
        return -1;
    }
}

int Database::GroupId(std::string const& groupName) const
{
    QSqlQuery groupId(iSqliteDatabase);
    groupId.prepare("SELECT id FROM Groups WHERE name=?");
    groupId.addBindValue(groupName.c_str());
    if(!groupId.exec())
        qDebug() << groupId.lastError().text();

    if(groupId.first())
    {
        return groupId.value(0).toInt();
    }
    else
    {
        return -1;
    }
}

