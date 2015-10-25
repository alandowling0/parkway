#pragma once

#include <QString>

class Parent
{
public:
    Parent(const QString &name, const QString &email, const QString &phone);

    QString Name() const;
    QString Email() const;
    QString Phone() const;

private:
    QString iName;
    QString iEmail;
    QString iPhone;
};

