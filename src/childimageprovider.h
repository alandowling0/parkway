#pragma once

#include <QQuickImageProvider>
#include <QMutex>

class ChildrenListModel;

class ChildImageProvider : public QQuickImageProvider
{
public:
    ChildImageProvider(ChildrenListModel const& childrenListModel);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    QMutex iMutex;
    ChildrenListModel const& iChildrenListModel;
};
