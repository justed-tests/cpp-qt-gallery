#pragma once

#include <QWidget>
#include <QItemSelection>
#include <QItemSelectionModel>

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

private slots:
  void deletePicture();
  void loadPicture(const QItemSelection& selected);

private:
  void updatePicturePixmap();

private:
  Ui::PictureWidget *ui;
  ThumbnailProxyModel* mModel;
  QItemSelectionModel* mSelectionModel;
  QPixmap mPixmap;
};
