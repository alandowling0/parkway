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
    enum ChildRole {
        NameRole = Qt::UserRole + 1,
        ImageRole,
        GroupRole,
        AgeRole
    };

    ChildrenListModel(QObject *parent = 0);

    Q_INVOKABLE void addChild(QString const& name, QString const& image, QString const& group, QString const& dateOfBirth);
    Q_INVOKABLE QString getChildName(int index) const;

    Q_INVOKABLE void sortByName();
    Q_INVOKABLE void sortByAge();
    Q_INVOKABLE void sortByGroup();

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
    void addChild(Child const& child);
    void sort(ChildRole sortRole);

private:
    QList<Child> iChildren;

    Database iDatabase;

    ChildRole iSortRole;
    Qt::SortOrder iSortOrder;
};
