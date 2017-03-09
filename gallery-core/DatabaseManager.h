#pragma once

#include <QString>

#include "AlbumDao.h"

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
  const AlbumDao albumDao;
private:
  QSqlDatabase* mDatabase;
};
