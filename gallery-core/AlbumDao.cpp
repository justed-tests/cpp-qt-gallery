#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

#include "AlbumDao.h"

AlbumDao::AlbumDao(QSqlDatabase& database)
  :mDatabase(database)
{
}

void AlbumDao::init() const
{
  if (!mDatabase.tables().contains("albums")) {
    QSqlQuery query(mDatabase);
    query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
  }
}
