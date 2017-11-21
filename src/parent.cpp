#include "parent.h"

#include <QString>

Parent::Parent(const QString &name, const QString &email, const QString &phone)
    :iName(name), iEmail(email), iPhone(phone)
{
}

QString Parent::Name() const
{
    return iName;
}

QString Parent::Email() const
{
    return iEmail;
}

QString Parent::Phone() const
{
    return iPhone;
}

