#pragma once

#include <QAbstractListModel>
#include <QList>
#include <vector>
#include <QtSql>
#include <QUrl>
#include "child.h"
#include "database.h"

class ChildrenListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ChildRole {
        NameRole = Qt::UserRole + 1,
        GroupRole,
        AgeRole,
        ImageRole
    };

    ChildrenListModel(QObject *parent = 0);

    Q_INVOKABLE void addChild(QString const& name, QString const& dateOfBirth, QString const& group, QUrl const& imageFilePath);
    Q_INVOKABLE void removeChild(QString const& name);
    Q_INVOKABLE void sortByName();
    Q_INVOKABLE void sortByAge();
    Q_INVOKABLE void sortByGroup();

    QImage getImage(QString const& name) const;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

public slots:
    void onDatabaseUpdated();

private:
    void refresh();
    void sort();
    void toggleSortOrder();

private:
    std::vector<Child> iChildren;

    Database iDatabase;

    ChildRole iSortRole;
    Qt::SortOrder iSortOrder;
};
