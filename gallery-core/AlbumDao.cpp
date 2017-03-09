#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QStringList>

#include "AlbumDao.h"

#include "Album.h"

using namespace std;

AlbumDao::AlbumDao(QSqlDatabase& database)
  : mDatabase(database)
{
}

void AlbumDao::init() const
{
  if (!mDatabase.tables().contains("albums")) {
    QSqlQuery query(mDatabase);
    query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
  }
}

void AlbumDao::addAblum(Album& album) const
{
  QSqlQuery query(mDatabase);
  query.prepare("INSERT INTO albums (name) VALUES(:name)");
  query.bindValue(":name", album.name());
  query.exec();
  album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album&) const
{
  // someday
}

void AlbumDao::removeAlbum(int) const
{
  // it will be implemented
}

unique_ptr<vector<unique_ptr<Album>>> AlbumDao::albums() const
{
  QSqlQuery query("SELECT * FROM albums", mDatabase);
  query.exec();

  unique_ptr<vector<unique_ptr<Album>>> list (new vector<unique_ptr<Album>>());

  while(query.next()) {
    unique_ptr<Album> album(new Album());

    album->setId(query.value("id").toInt());
    album->setName(query.value("name").toString());

    list->push_back(move(album));
  }

  return list;
}
