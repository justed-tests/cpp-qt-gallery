#include "PictureModel.h"

#include <QDebug>

#include "DatabaseManager.h"
#include "AlbumModel.h"


using namespace std;

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
  QAbstractListModel(parent),
  mDb(DatabaseManager::instance()),
  mAlbumId(-1),
  mPictures(new vector <unique_ptr<Picture>>())
{
  connect(
    &albumModel, &AlbumModel::rowsRemoved,
    this,        &PictureModel::deletePicturesForAlbum
  );
}

void PictureModel::setAlbumId(int albumId)
{
  beginResetModel();

  mAlbumId = albumId;
  loadPictures(mAlbumId);

  endResetModel();
}

void PictureModel::loadPictures(int albumId)
{
  if (albumId <= 0) {
    mPictures.reset(new vector<unique_ptr<Picture>>());
    return;
  }

  mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

QModelIndex PictureModel::addPicture(const Picture& picture)
{
  int rowIndex = rowCount();

  beginInsertRows(QModelIndex(), rowIndex, rowIndex);

  unique_ptr<Picture> newPicture(new Picture(picture));
  mDb.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
  mPictures->push_back(move(newPicture));

  endInsertRows();

  return index(rowIndex, 0);
}

int PictureModel::rowCount(const QModelIndex&) const
{
  return mPictures->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
  if (!isIndexValid(index)) {
    return QVariant();
  }

  const Picture& picture = *mPictures->at(index.row());
  
  switch (role) {
    case PictureRole::FilePathRole:
      return picture.fileUrl();
    default:
      return QVariant();
  }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
  if (row < 0
     || row >= rowCount()
     || count < 0
     || (row + count) > rowCount()) {
    return false;
  }

  beginRemoveRows(parent, row, row + count - 1);
  int countLeft = count;

  while (countLeft--) {
    const Picture& picture = *mPictures->at(row + countLeft);
    mDb.pictureDao.removePicture(picture.id());
  }

  mPictures->erase(mPictures->begin() + row,
                   mPictures->begin() + row + count);

  endRemoveRows();
  return true;
}

bool PictureModel::isIndexValid(const QModelIndex& index) const
{
  return index.isValid();
}

//void PictureModel::rowsRemoved(const QModelIndex & parent, int start, int end)
void PictureModel::deletePicturesForAlbum()
{
  qWarning() << "implement me!";
}
