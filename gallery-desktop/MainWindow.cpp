#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemSelectionModel>

#include "AlbumModel.h"
#include "PictureModel.h"

#include "GalleryWidget.h"
#include "PictureWidget.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mGalleryWidget(),
  mPictureWidget()
{
  ui->setupUi(this);

  AlbumModel* albumModel = new AlbumModel(this);
  QItemSelectionModel* albumSelectionModel = new QItemSelectionModel(albumModel, this);

  mGalleryWidget->setAlbumModel(albumModel);
  mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);

  PictureModel* pictureModel = new PictureModel(*albumModel, this);
  ThumbnailProxyModel* thumbnailModel = new ThumbnailProxyModel(this);
  thumbnailModel->setSourceModel(pictureModel);

  QItemSelectionModel* PictureSelectionModel = new QItemSelectionModel(pictureModel, this);

  mGalleryWidget->setPictureModel(thumbnailModel);
  mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
  mPictureWidget->setModel(thumbnailModel);
  mPictureWidget->setSelectionModel(pictureSelectionModel);
}

MainWindow::~MainWindow()
{
  delete ui;
}
