#pragma once

#include <QWidget>
#include <QItemSelectionModel>

namespace Ui {
class GalleryWidget;
}

class AlbumModel;
class ThumbnailProxyModel;

class GalleryWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GalleryWidget(QWidget *parent = 0);
  ~GalleryWidget();

  void setAlbumModel(AlbumModel* albumModel);
  void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);
  void setPictureModel(ThumbnailProxyModel* pictureModel);
  void setPictureSelectionModel(QItemSelectionModel* selectionModel);

signals:
  void paintingActive(const QModelIndex& index);

private:
  Ui::GalleryWidget *ui;
};
