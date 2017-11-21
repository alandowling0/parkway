#pragma once

#include <QString>

class Child
{
public:
    Child(QString const& name, QString const& dateOfBirth, QString const& group);

    QString Name() const;
    QString DateOfBirth() const;
    QString Group() const;

private:
    QString iName;
    QString iDateOfBirth;
    QString iGroup;
};

namespace ChildUtils
{
    bool CompareName(Child const& child, Child const& other);
    bool CompareAge(Child const& child, Child const& other);
    bool CompareGroup(Child const& child, Child const& other);

    QString Age(Child const& child);
}
