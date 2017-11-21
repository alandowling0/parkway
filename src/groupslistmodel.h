#pragma once

#include <QObject>
#include <QList>
#include <QString>
#include "database.h"

class GroupsListModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList groupNames READ groupNames NOTIFY groupNamesChanged)

public:
    GroupsListModel(QObject *parent = nullptr);

    QStringList groupNames() const;

signals:
    void groupNamesChanged();

private:
    QStringList iGroupNames;

    Database iDatabase;
};

