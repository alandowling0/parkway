#include "groupslistmodel.h"
#include <QDebug>
#include <cassert>


GroupsListModel::GroupsListModel(QObject *parent)
    :QObject(parent)
{
   auto groups = iDatabase.GetAllGroups();

   for(auto const& group : groups)
   {
       iGroupNames.push_back(group);
   }

   emit groupNamesChanged();
}

QStringList GroupsListModel::groupNames() const
{
    return iGroupNames;
}




