#pragma once

#include <QString>
#include <QImage>

class Child
{
public:
    Child(QString const& name, QString const& dateOfBirth, QString const& group, QImage const& image);

    QString name() const;
    QString dateOfBirth() const;
    QString group() const;
    QImage image() const;

private:
    QString iName;
    QString iDateOfBirth;
    QString iGroup;
    QImage iImage;
};

namespace ChildUtils
{
    bool compareName(Child const& child, Child const& other);
    bool compareAge(Child const& child, Child const& other);
    bool compareGroup(Child const& child, Child const& other);

    double age(Child const& child);
}
