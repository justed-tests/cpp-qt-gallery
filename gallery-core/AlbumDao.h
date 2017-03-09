#pragma once

#include <QVector>

class QSqlDatabase;

class Album;

class AlbumDao
{
public:
  AlbumDao(QSqlDatabase& database);
  void init() const;

  void addAblum(Album& album) const;
  void updateAlbum(const Album& album) const;
  void removeAlbum(int id) const;
  QVector<Album*> albums() const;
private:
  QSqlDatabase& mDatabase;
};
