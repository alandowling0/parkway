#include "childimageprovider.h"
#include "childrenlistmodel.h"

ChildImageProvider::ChildImageProvider(ChildrenListModel const& childrenListModel) :
    QQuickImageProvider(QQuickImageProvider::Image),
    iChildrenListModel(childrenListModel)
{

}

QImage ChildImageProvider::requestImage(QString const& id, QSize */*size*/, QSize const& /*requestedSize*/)
{
    QMutexLocker locker(&iMutex);

    return iChildrenListModel.getImage(id);
}
