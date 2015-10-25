#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtSql>

#include "parent.h"
#include "database.h"

class ParentsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ParentRoles {
        NameRole = Qt::UserRole + 1,
        EmailRole,
        PhoneRole
    };

    Q_INVOKABLE void setChild(QString const& childName);

    ParentsListModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
    void AddParent(Parent const& parent);
    void ClearParents();


private:
    QList<Parent> iParents;

    Database iDatabase;
};
