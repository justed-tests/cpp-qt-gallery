#include "DatabaseManager.h"

#include <QSqlDatabase>

DatabaseManager& DatabaseManager::instance()
{
  static DatabaseManager singleton;
  return singleton;
}

DatabaseManager::DatabaseManager(const QString& path)
  //: mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
    //albumDao(*mDatabase), // ??
    //pictureDao(*mDatabase) // ??
{
  mDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
  albumDao = new AlbumDao(*mDatabase);
  pictureDao = new PictureDao(*mDatabase);

  mDatabase->setDatabaseName(path);
  mDatabase->open();

  albumDao->init();
}

DatabaseManager::~DatabaseManager()
{
  mDatabase->close();
  delete mDatabase;
}
