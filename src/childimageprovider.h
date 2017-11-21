#pragma once

#include <QQuickImageProvider>
#include <QMutex>
#include "database.h"

class ChildImageProvider : public QQuickImageProvider
{
public:
    ChildImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    Database iDatabase;
    QMutex iMutex;
};
