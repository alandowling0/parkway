#include "child.h"
#include <sstream>
#include <iomanip>
#include <QString>
#include <QDate>

Child::Child(QString const& name, QString const& dateOfBirth, QString const& group, QImage const& image)
    :iName(name), iDateOfBirth(dateOfBirth), iGroup(group), iImage(image)
{
}

QString Child::name() const
{
    return iName;
}

QString Child::dateOfBirth() const
{
    return iDateOfBirth;
}

QString Child::group() const
{
    return iGroup;
}

QImage Child::image() const
{
    return iImage;
}


bool ChildUtils::compareName(Child const& child, Child const& other)
{
    return QString::localeAwareCompare(child.name(), other.name()) < 0;
}

bool ChildUtils::compareAge(Child const& child, Child const& other)
{
    return ChildUtils::age(child) < ChildUtils::age(other);
}

bool ChildUtils::compareGroup(Child const& child, Child const& other)
{
    return QString::localeAwareCompare(child.group(), other.group()) < 0;
}

double ChildUtils::age(Child const& child)
{
    auto dob = QDate::fromString(child.dateOfBirth(), "dd/MM/yyyy");
    auto today = QDate::currentDate();

    auto days = dob.daysTo(today);

    return days / 365.0;
}
