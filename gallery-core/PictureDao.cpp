#include "PictureDao.h"
#include "Picture.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include <QDebug>

using namespace std;

PictureDao::PictureDao(QSqlDatabase& database)
  : mDatabase(database)
{
}

void PictureDao::init() const
{
  if (!mDatabase.tables().contains("pictures")){
    QSqlQuery query(mDatabase);
    auto res = query.exec(QString("CREATE TABLE pictures ")
       + "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
       + "album_id INTEGER, "
       + "url TEXT)"
    );
  }
}

void PictureDao::addPictureInAlbum(int albumId, Picture& picture) const
{
  QSqlQuery query(mDatabase);
  query.prepare("INSERT INTO pictures (url, album_id) VALUES(:url, :album_id)");
  query.bindValue(":url", picture.fileUrl());
  query.bindValue(":album_id", albumId);
  query.exec();
  picture.setId(query.lastInsertId().toInt());
}

void PictureDao::removePicture(int id) const
{
  QSqlQuery query(mDatabase);
  query.prepare("DELETE pictures WHERE id=:id");
  query.bindValue(":id", id);
  query.exec();
}

void PictureDao::removePicturesFromAlbum(int albumId) const
{
  QSqlQuery query(mDatabase);
  query.prepare("DELETE pictures WHERE album_id=:album_id");
  query.bindValue(":album_id", albumId);
  query.exec();
}

unique_ptr<vector<unique_ptr<Picture>>> PictureDao::picturesForAlbum(int albumId) const
{
  QSqlQuery query(mDatabase);
  query.prepare("SELECT * FROM pictures WHERE album_id=:album_id");

  query.bindValue(":album_id", albumId);
  query.exec();

  unique_ptr<vector<unique_ptr<Picture>>> list (new vector<unique_ptr<Picture>>());

  while(query.next()) {
    unique_ptr<Picture> picture(new Picture());

    picture->setId(query.value("id").toInt());
    picture->setFileUrl(query.value("url").toString());
    picture->setAlbumId(albumId);

    list->push_back(move(picture));
  }

  return list;

}
