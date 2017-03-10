#include "AlbumWidget.h"
#include "ui_AlbumWidget.h"

#include <QInputDialog>
#include <QFileDialog>

#include "AlbumModel.h"
#include "PictureModel.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AlbumWidget),
  mAlbumModel(nullptr),
  mAlbumSelectionModel(nullptr),
  mPictureModel(nullptr),
  mPictureSelectionModel(nullptr)
{
  ui->setupUi(this);
  clearUi();

  ui->thumbnailListView->setSpacing(5);
  ui->thumbnailListView->setResizeMode(QListView::Adjust);
  ui->thumbnailListView->setFlow(QListView::LeftToRight);
  ui->thumbnailListView->setWrapping(true);

  connect(
    ui->thumbnailListView, &QListView::doubleClicked,
    this,                  &AlbumWidget::pictureActivated
  );

  connect(
    ui->deleteButton, &QPushButton::clicked,
    this,             &AlbumWidget::deleteAlbum
  );

  connect(
    ui->editButton, &QPushButton::clicked,
    this,           &AlbumWidget::editAlbum
  );

  connect(
    ui->addPicturesButton, &QPushButton::clicked,
    this,                  &AlbumWidget::addPictures
  );
}

AlbumWidget::~AlbumWidget()
{
  delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel* albumModel)
{
  mAlbumModel = albumModel;

  connect(
    mAlbumModel, &QAbstractItemModel::dataChanged,
    [this] (const QModelIndex &topLeft) {
      if (topLeft == mAlbumSelectionModel->currentIndex()) {
        loadAlbum(topLeft);
      }
    }
  );
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel)
{
  mAlbumSelectionModel = albumSelectionModel;

  connect(
    mAlbumSelectionModel, &QItemSelectionModel::selectionChanged,
    [this] (const QItemSelection &selected) {
      if (selected.isEmpty()) {
        clearUi();
        return;
      }
      loadAlbum(selected.indexes().first());
    }
  );
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel* pictureModel)
{
  mPictureModel = pictureModel;
  //FIXME: doesnt work
  //ui->thumbnailListView->setModel(mPictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
  ui->thumbnailListView->setSelectionModel(selectionModel);
}

void AlbumWidget::deleteAlbum()
{
  if (mAlbumSelectionModel->selectedIndexes().isEmpty()) {
    return;
  }

  int row = mAlbumSelectionModel->currentIndex().row();
  mAlbumModel->removeRow(row);

  QModelIndex previousModelIndex = mAlbumModel->index(row - 1, 0);

  if (previousModelIndex.isValid()) {
    mAlbumSelectionModel->setCurrentIndex(previousModelIndex,
        QItemSelectionModel::SelectCurrent);
    return;
  }

  QModelIndex nextModelIndex = mAlbumModel->index(row, 0);
  
  if (nextModelIndex.isValid()) {
    mAlbumSelectionModel->setCurrentIndex(nextModelIndex,
        QItemSelectionModel::SelectCurrent);
    return;
  }
}

void AlbumWidget::editAlbum()
{
}

void AlbumWidget::addPictures()
{
}

void AlbumWidget::clearUi()
{
}

void AlbumWidget::loadAlbum(const QModelIndex& albumIndex)
{
}
