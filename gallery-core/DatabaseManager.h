#pragma once

#include <QString>

#include "AlbumDao.h"
#include "PictureDao.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
  static DatabaseManager& instance();
  ~DatabaseManager();
protected:
  DatabaseManager(const QString& path = DATABASE_FILENAME);
  DatabaseManager& operator=(const DatabaseManager& rhs);

public:
  AlbumDao* albumDao;
  PictureDao* pictureDao;
private:
  QSqlDatabase* mDatabase;
};
