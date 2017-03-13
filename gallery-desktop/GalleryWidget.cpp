#include "GalleryWidget.h"
#include "ui_GalleryWidget.h"

GalleryWidget::GalleryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryWidget)
{
    ui->setupUi(this);
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
}

void GalleryWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
}
