#pragma once

#include <QString>
#include <QImage>

class Child
{
public:
    Child(QString const& name, QString const& dateOfBirth, QString const& group, QImage const& image);

    QString Name() const;
    QString DateOfBirth() const;
    QString Group() const;
    QImage Image() const;

private:
    QString iName;
    QString iDateOfBirth;
    QString iGroup;
    QImage iImage;
};

namespace ChildUtils
{
    bool CompareName(Child const& child, Child const& other);
    bool CompareAge(Child const& child, Child const& other);
    bool CompareGroup(Child const& child, Child const& other);

    double Age(Child const& child);
}
