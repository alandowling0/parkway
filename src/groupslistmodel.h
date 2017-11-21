#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtSql>
#include <string>
#include "database.h"

class GroupsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum GroupRoles {
        NameRole = Qt::UserRole + 1,
    };

    Q_INVOKABLE QString getGroupName(int index) const;

    GroupsListModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
    void AddGroup(std::string const& child);

private:
    QList<std::string> iGroupNames;

    Database iDatabase;
};

