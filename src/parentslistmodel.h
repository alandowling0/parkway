#pragma once

#include <QAbstractListModel>
#include <vector>
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

public slots:
    void onDatabaseUpdated();

private:
    void refresh();

    std::vector<Parent> iParents;
    QString iChildName;
    Database iDatabase;
};
