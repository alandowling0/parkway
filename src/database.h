#pragma once

#include <QString>
#include <QObject>
#include <QtSql>
#include "child.h"
#include "parent.h"
#include "timetable.h"

class Database : public QObject
{
    Q_OBJECT

public:
    Database(QObject* parent = nullptr);
    ~Database();

    std::vector<Child> children() const;
    std::vector<QString> groups() const;
    std::vector<Parent> parents() const;
    std::vector<Parent> parents(QString const& childName) const;
    std::vector<Timetable> timetables(QString const& childName) const;

    void addChild(Child const& child);
    void removeChild(QString const& childName);
    void addParent(Parent const& parent);
    void removeParent(QString const& parentName);
    void addRelationship(QString childName, QString parentName);



    static const QString DATABASE_NAME;

signals:
    void updated();

private:
     int childId(QString const& childName) const;
     int parentId(QString const& parentName) const;
     int groupId(QString const& groupName) const;

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

