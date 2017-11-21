#include "groupslistmodel.h"
#include <QDebug>
#include <cassert>


GroupsListModel::GroupsListModel(QObject *parent)
    :QAbstractListModel(parent)
{
   auto groups = iDatabase.GetAllGroups();

   for(auto const& group : groups)
   {
       AddGroup(group);
   }
}

QString GroupsListModel::getGroupName(int index) const
{
    auto modelIndex =  QAbstractItemModel::createIndex(index, 0);
    QVariant name = data(modelIndex, NameRole);

    return name.toString();
}

QHash<int, QByteArray> GroupsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

QVariant GroupsListModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    auto row = index.row();

    if(row < iGroupNames.size())
    {
        auto group = iGroupNames.at(row);

        switch (role)
        {
        case NameRole:
            data = QVariant(group.c_str());
            break;
        default:
            assert(false);
        }
    }

    return data;
}

int GroupsListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return iGroupNames.size();
}

void GroupsListModel::AddGroup(std::string const& group)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iGroupNames.push_back(group);
    endInsertRows();
}

