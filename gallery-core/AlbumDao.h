#pragma once

#include <memory>

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
  //QVector<Album*> albums() const;
  std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums() const;
private:
  QSqlDatabase& mDatabase;
};
