#include "childimageprovider.h"

ChildImageProvider::ChildImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage ChildImageProvider::requestImage(const QString &id, QSize */*size*/, const QSize &/*requestedSize*/)
{
    QMutexLocker locker(&iMutex);

    auto data = iDatabase.GetImageData(id.toStdString());

    return QImage::fromData(data);
}
