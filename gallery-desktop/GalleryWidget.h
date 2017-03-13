#pragma once

#include <QWidget>

namespace Ui {
class GalleryWidget;
}

class GalleryWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GalleryWidget(QWidget *parent = 0);
  ~GalleryWidget();

private:
  Ui::GalleryWidget *ui;
};
