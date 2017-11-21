#include "childimageprovider.h"

ChildImageProvider::ChildImageProvider() :
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage ChildImageProvider::requestImage(QString const& id, QSize */*size*/, QSize const& /*requestedSize*/)
{
    QMutexLocker locker(&iMutex);

    auto data = iDatabase.GetImageData(id.toStdString());

    return QImage::fromData(data);
}
