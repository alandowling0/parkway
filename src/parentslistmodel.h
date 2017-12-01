#pragma once

#include <QAbstractListModel>
#include <vector>
#include <QtSql>

#include "parent.h"
#include "database.h"

class ParentsListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList parentsNames READ parentsNames NOTIFY parentNamesChanged)

public:
    enum ParentRoles {
        NameRole = Qt::UserRole + 1,
        EmailRole,
        PhoneRole
    };

    ParentsListModel(Database& database, QObject *parent = 0);

    Q_INVOKABLE void setChildFilter(QString const& childName);
    Q_INVOKABLE void clearChildFilter();

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    QStringList parentsNames() const;

signals:
    void parentNamesChanged();

public slots:
    void onDatabaseUpdated();

private:
    void refresh();

    Database& iDatabase;
    std::vector<Parent> iParents;

    bool iChildFilterOn;
    QString iChildFilter;
};
