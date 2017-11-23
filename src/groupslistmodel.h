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

public slots:
    void onDatabaseUpdated();

signals:
    void groupNamesChanged();

private:
    void refresh();

    QStringList iGroupNames;
    Database iDatabase;
};

