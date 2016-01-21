#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtSql>
#include "child.h"
#include "database.h"

class ChildrenListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ChildRoles {
        NameRole = Qt::UserRole + 1,
        ImageRole,
        GroupRole,
        AgeRole
    };

    Q_INVOKABLE QString getChildName(int index) const; //Enable various UI components to know the name of the currently selected child
    Q_INVOKABLE void sortBy(int column);

    ChildrenListModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

private:
    void AddChild(Child const& child);

private:
    QList<Child> iChildren;

    Database iDatabase;
};
