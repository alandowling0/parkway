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

    std::vector<Child> GetAllChildren() const;
    std::vector<Parent> GetAllParents() const;
    std::vector<QString> GetAllGroups() const;
    std::vector<Parent> GetParents(QString const& childName) const;
    std::vector<Timetable> GetTimetables(QString const& childName) const;

    void AddChild(Child const& child);

    static const QString DATABASE_NAME;

signals:
    void updated();

private:
     int ChildId(QString const& childName) const;
     int GroupId(QString const& groupName) const;

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

