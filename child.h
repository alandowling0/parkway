#pragma once

#include <QString>

class Child
{
public:
    Child(const QString &name, const QString &image, const QString &group, const QString &dateOfBirth);

    QString Name() const;
    QString Image() const;
    QString Group() const;
    QString Age() const;

private:
    QString iName;
    QString iImage;
    QString iGroup;
    QString iDateOfBirth;
};

namespace ChildUtils
{
    bool CompareName(Child const& child, Child const& other);
    bool CompareAge(Child const& child, Child const& other);
    bool CompareGroup(Child const& child, Child const& other);
}
