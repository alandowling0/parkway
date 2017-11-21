#include "parentslistmodel.h"
#include <QDebug>
#include <cassert>


ParentsListModel::ParentsListModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void ParentsListModel::setChild(QString const& childName)
{
    ClearParents();

    auto parents = iDatabase.GetParents(childName.toStdString());

    for(auto const& parent : parents)
    {
        AddParent(parent);
    }
}

QHash<int, QByteArray> ParentsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[EmailRole] = "email";
    roles[PhoneRole] = "phone";
    return roles;
}

QVariant ParentsListModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    auto row = index.row();

    if(row < iParents.size())
    {
        auto parent = iParents.at(row);

        switch (role)
        {
        case NameRole:
            data = QVariant(parent.Name());
            break;
        case EmailRole:
            data = QVariant(parent.Email());
            break;
        case PhoneRole:
            data = QVariant(parent.Phone());
            break;
        default:
            assert(false);
        }
    }

    return data;
}

int ParentsListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return iParents.size();
}

void ParentsListModel::AddParent(Parent const& parent)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iParents.push_back(parent);
    endInsertRows();
}

void ParentsListModel::ClearParents()
{
    if(!iParents.empty())
    {
        beginRemoveRows(QModelIndex(), 0, rowCount()-1);
        iParents.clear();
        endRemoveRows();
    }
}
