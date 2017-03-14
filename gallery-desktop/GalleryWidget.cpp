#include "GalleryWidget.h"
#include "ui_GalleryWidget.h"
#include "AlbumWidget.h"

GalleryWidget::GalleryWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GalleryWidget)
{
  ui->setupUi(this);

  connect(
    ui->albumWidget, &AlbumWidget::pictureActivated,
    this,                &GalleryWidget::paintingActive
  );
}

GalleryWidget::~GalleryWidget()
{
  delete ui;
}

void GalleryWidget::setAlbumModel(AlbumModel* albumModel)
{
  ui->albumListWidget->setModel(albumModel);
  ui->albumWidget->setAlbumModel(albumModel);
}

void GalleryWidget::setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel)
{
  ui->albumListWidget->setSelectionModel(albumSelectionModel);
  ui->albumWidget->setAlbumSelectionModel(albumSelectionModel);
}

void GalleryWidget::setPictureModel(ThumbnailProxyModel* pictureModel)
{
  ui->albumWidget->setPictureModel(pictureModel);
}

void GalleryWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
  ui->albumWidget->setPictureSelectionModel(selectionModel);
}
