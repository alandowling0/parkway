#include "database.h"
#include <cassert>

const QString Database::DATABASE_NAME = "parkway.db";

Database::Database(QObject* parent) :
    QObject(parent)
{
    auto names = QSqlDatabase::connectionNames();
    auto count = names.size();
    iConnectionName = QString::number(count);
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

std::vector<Child> Database::children() const
{
    std::vector<Child> children;

    QSqlQuery query(iSqliteDatabase);

    query.prepare("SELECT Children.name, Children.dob, Groups.name, Children.imageData "
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
        auto imageData = query.value(3).toByteArray();

        children.emplace_back(name, dob, group, QImage::fromData(imageData));
    }

    return children;
}

std::vector<Parent> Database::parents() const
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

std::vector<QString> Database::groups() const
{
    std::vector<QString> groups;

    QSqlQuery query(iSqliteDatabase);

    query.prepare("SELECT Groups.name "
                  "FROM Groups ");

    if(!query.exec())
        qDebug() << query.lastError().text();

    while(query.next())
    {
        auto name = query.value(0).toString();

        groups.emplace_back(name);
    }

    return groups;
}

std::vector<Parent> Database::parents(QString const& childName) const
{
    std::vector<Parent> parents;

    QSqlQuery relation(iSqliteDatabase);
    relation.prepare("SELECT parent FROM Relations WHERE child=?");
    relation.addBindValue(childId(childName));

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

std::vector<Timetable> Database::timetables(QString const& childName) const
{
    std::vector<Timetable> timetables;

    QSqlQuery timetable(iSqliteDatabase);
    timetable.prepare("SELECT term, monday, tuesday, wednesday, thursday, friday "
                      "FROM Timetables WHERE child=?");
    timetable.addBindValue(childId(childName));

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

        timetables.emplace_back(childName, term, mon, tue, wed, thu, fri);
    }

    return timetables;
}

void Database::addChild(Child const& child)
{
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    child.image().save(&buffer, "JPG");
    auto imageData = buffer.data();

    QSqlQuery query(iSqliteDatabase);
    query.prepare("INSERT INTO Children (name, dob, \"group\", imageData) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(child.name());
    query.addBindValue(child.dateOfBirth());
    query.addBindValue(groupId(child.group()));
    query.addBindValue(imageData);

    if(!query.exec())
        qDebug() << query.lastError().text();

    emit updated();
}

void Database::removeChild(QString const& childName)
{
    QSqlQuery query(iSqliteDatabase);
    query.prepare("DELETE FROM Relations WHERE child = (?)");
    query.addBindValue(childId(childName));
    if(!query.exec())
        qDebug() << query.lastError().text();

    query.prepare("DELETE FROM Timetables WHERE child = (?)");
    query.addBindValue(childId(childName));
    if(!query.exec())
        qDebug() << query.lastError().text();

    query.prepare("DELETE FROM Children WHERE name = (?)");
    query.addBindValue(childName);
    if(!query.exec())
        qDebug() << query.lastError().text();

    emit updated();
}

void Database::addRelationship(QString childName, QString parentName)
{
    auto child = childId(childName);
    auto parent = parentId(parentName);

    if(child >= 0 && parent >= 0)
    {
        QSqlQuery query(iSqliteDatabase);
        query.prepare("INSERT INTO Relations (child, parent) VALUES (?, ?)");
        query.addBindValue(child);
        query.addBindValue(parent);

        if(!query.exec())
            qDebug() << query.lastError().text();

        emit updated();
    }
}

int Database::childId(QString const& childName) const
{
    QSqlQuery childId(iSqliteDatabase);
    childId.prepare("SELECT id FROM Children WHERE name=?");
    childId.addBindValue(childName);
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

int Database::parentId(QString const& parentName) const
{
    QSqlQuery parentId(iSqliteDatabase);
    parentId.prepare("SELECT id FROM Parents WHERE name=?");
    parentId.addBindValue(parentName);
    if(!parentId.exec())
        qDebug() << parentId.lastError().text();

    if(parentId.first())
    {
        return parentId.value(0).toInt();
    }
    else
    {
        return -1;
    }
}

int Database::groupId(QString const& groupName) const
{
    QSqlQuery groupId(iSqliteDatabase);
    groupId.prepare("SELECT id FROM Groups WHERE name=?");
    groupId.addBindValue(groupName);
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

