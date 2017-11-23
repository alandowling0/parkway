#pragma once

#include <QString>

class Parent
{
public:
    Parent(const QString &name, const QString &email, const QString &phone);

    QString name() const;
    QString email() const;
    QString phone() const;

private:
    QString iName;
    QString iEmail;
    QString iPhone;
};

