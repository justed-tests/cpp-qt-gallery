#pragma once
#include "gallery-core_global.h"

#include <QString>

class GALLERYCORESHARED_EXPORT Album
{

public:
  explicit Album(const QString& name = "");
  int id() const;
  void setId(int id);
  QString name() const;
  void setName(const QString& name);

private:
  int mId;
  QString mName;
};
