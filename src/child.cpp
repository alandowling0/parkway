#include "child.h"
#include <sstream>
#include <iomanip>
#include <QString>
#include <QDate>

Child::Child(QString const& name, QString const& dateOfBirth, QString const& group)
    :iName(name), iDateOfBirth(dateOfBirth), iGroup(group)
{
}

QString Child::Name() const
{
    return iName;
}

QString Child::DateOfBirth() const
{
    return iDateOfBirth;
}

QString Child::Group() const
{
    return iGroup;
}



bool ChildUtils::CompareName(Child const& child, Child const& other)
{
    return child.Name() < other.Name();
}

bool ChildUtils::CompareAge(Child const& child, Child const& other)
{
    return ChildUtils::Age(child) < ChildUtils::Age(other);
}

bool ChildUtils::CompareGroup(Child const& child, Child const& other)
{
    return child.Group() < other.Group();
}

QString ChildUtils::Age(Child const& child)
{
    auto dob = QDate::fromString(child.DateOfBirth(), "dd/MM/yyyy");
    auto today = QDate::currentDate();

    auto days = dob.daysTo(today);

    auto years = days / 365.0;

    std::stringstream ss;
    ss << std::setprecision(3) << years;

    return QString::fromStdString(ss.str());
}
