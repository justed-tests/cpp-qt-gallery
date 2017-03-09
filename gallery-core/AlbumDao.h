#pragma once

class QSqlDatabase;

class AlbumDao
{
public:
  AlbumDao(QSqlDatabase& database);
  void init() const;
private:
  QSqlDatabase& mDatabase;
};
