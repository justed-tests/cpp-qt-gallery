#pragma once

#include <QWidget>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QModelIndex>

namespace Ui {
class PictureWidget;
}

class PictureModel;
class ThumbnailProxyModel;

class PictureWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PictureWidget(QWidget *parent = 0);
  ~PictureWidget();

  void setModel(ThumbnailProxyModel* model);
  void setSelectionModel(QItemSelectionModel* selectionModel);

signals:
  void backToGallery();

protected:
  void resizeEvent(QResizeEvent* event) override;

public slots:
  void loadPicture(const QModelIndex& index);

private slots:
  void deletePicture();

private:
  void updatePicturePixmap();

private:
  Ui::PictureWidget *ui;
  ThumbnailProxyModel* mModel;
  QItemSelectionModel* mSelectionModel;
  QPixmap mPixmap;
};
