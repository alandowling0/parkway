#include "groupslistmodel.h"
#include <QDebug>
#include <cassert>


GroupsListModel::GroupsListModel(QObject *parent)
    :QObject(parent)
{
    refresh();

    connect(&iDatabase, &Database::updated, this, &GroupsListModel::onDatabaseUpdated);
}

QStringList GroupsListModel::groupNames() const
{
    return iGroupNames;
}

void GroupsListModel::onDatabaseUpdated()
{
    refresh();
}

void GroupsListModel::refresh()
{
    iGroupNames.clear();

    for(auto const& group : iDatabase.groups())
    {
        iGroupNames.push_back(group);
    }

    emit groupNamesChanged();
}



