#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemSelectionModel>

#include "AlbumModel.h"
#include "PictureModel.h"

#include "GalleryWidget.h"
#include "PictureWidget.h"
#include "ThumbnailProxyModel.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mGalleryWidget( new GalleryWidget() ),
  mPictureWidget( new PictureWidget() ),
  mStackedWidget( new QStackedWidget() )
{
  ui->setupUi(this);

  AlbumModel* albumModel = new AlbumModel(this);
  QItemSelectionModel* albumSelectionModel = new QItemSelectionModel(albumModel, this);

  mGalleryWidget->setAlbumModel(albumModel);
  mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);

  PictureModel* pictureModel = new PictureModel(*albumModel, this);
  ThumbnailProxyModel* thumbnailModel = new ThumbnailProxyModel(this);
  thumbnailModel->setSourceModel(pictureModel);

  QItemSelectionModel* pictureSelectionModel = new QItemSelectionModel(pictureModel, this);

  mGalleryWidget->setPictureModel(thumbnailModel);
  mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
  mPictureWidget->setModel(thumbnailModel);
  mPictureWidget->setSelectionModel(pictureSelectionModel);

  connect(
    mGalleryWidget, &GalleryWidget::paintingActive,
    this,           &MainWindow::displayPicture
  );

  connect(
    mGalleryWidget, &GalleryWidget::paintingActive,
    mPictureWidget, &PictureWidget::loadPicture
  );

  connect(
    mPictureWidget, &PictureWidget::backToGallery,
    this,           &MainWindow::displayGallery
  );

  mStackedWidget->addWidget(mGalleryWidget);
  mStackedWidget->addWidget(mPictureWidget);

  displayGallery();
  setCentralWidget(mStackedWidget);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::displayGallery()
{
  mStackedWidget->setCurrentWidget(mGalleryWidget);
}

void MainWindow::displayPicture(const QModelIndex& index)
{
  mStackedWidget->setCurrentWidget(mPictureWidget);
}
