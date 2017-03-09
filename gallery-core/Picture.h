#pragma once

#include "gallery-core_global.h"

#include <QString>
#include <QUrl>

class GALLERYCORESHARED_EXPORT Picture
{

public:
  Picture(const QString& filepath = "");
  Picture(const QUrl& fileurl);

  int id() const;
  void setId(int id);

  int albumId() const;
  void setAlbumId(int id);

  QUrl fileUrl() const;
  void setFileUrl(const QUrl& fileUrl);

private:
  int mId;
  int mAlbumId;
  QUrl mFileUrl; 
};
