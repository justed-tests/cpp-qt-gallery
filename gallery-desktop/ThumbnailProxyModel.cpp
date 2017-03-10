#include "ThumbnailProxyModel.h"
#include "PictureModel.h"

const unsigned int THUMBNAIL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject*)
{
}

void ThumbnailProxyModel::generateThumbnails(const QModelIndex& startIndex, int count)
{
  if (!startIndex.isValid()) {
    return;
  }

  const QAbstractItemModel* model = startIndex.model();
  int lastIndex = startIndex.row() + count;

  for (int row = startIndex.row(); row < lastIndex; row++) {
    QString filepath = model->data(model->index(row, 0),
      PictureModel::PictureRole::FilePathRole).toString();

    QPixmap pixmap(filepath);

    auto thumbnail = new QPixmap(pixmap.scaled(THUMBNAIL_SIZE,
      THUMBNAIL_SIZE,
      Qt::KeepAspectRatio,
      Qt::SmoothTransformation));

    mThumbnails.insert(filepath, thumbnail);
  }

}

void ThumbnailProxyModel::reloadThumbnails()
{
  qDeleteAll(mThumbnails);
  mThumbnails.clear();
  generateThumbnails(index(0, 0), rowCount());
}

QVariant ThumbnailProxyModel::data(const QModelIndex& index, int role) const
{
  if (role != Qt::DecorationRole) {
    return QIdentityProxyModel::data(index, role);
  }

  QString filepath = sourceModel()->data(index,
    PictureModel::PictureRole::FilePathRole).toString();

  return *mThumbnails[filepath];
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
  QIdentityProxyModel::setSourceModel(sourceModel);

  if (!sourceModel) {
    return;
  }

  connect(
    sourceModel, &QAbstractItemModel::modelReset,
    [this] { reloadThumbnails(); }
  );

  connect(
    sourceModel, &QAbstractItemModel::rowsInserted,
    [this] (const QModelIndex&, int first, int last) {
      generateThumbnails(index(first, 0), last - first + 1);
    }
  );
}

PictureModel* ThumbnailProxyModel::pictureModel() const
{
  return static_cast<PictureModel*>(sourceModel());
}
