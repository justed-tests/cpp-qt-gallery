#include "PictureWidget.h"
#include "ui_PictureWidget.h"

#include "ThumbnailProxyModel.h"
#include "PictureModel.h"

#include <QDebug>

PictureWidget::PictureWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PictureWidget),
  mModel(nullptr),
  mSelectionModel(nullptr)
{
  ui->setupUi(this);

  connect(
    ui->backButton, &QPushButton::clicked,
    this,           &PictureWidget::backToGallery
  );
}

PictureWidget::~PictureWidget()
{
  delete ui;
}

void PictureWidget::setModel(ThumbnailProxyModel* model)
{
  mModel = model;
}

void PictureWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
  mSelectionModel = selectionModel;
}

void PictureWidget::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);
  updatePicturePixmap();
}

void PictureWidget::deletePicture()
{
}

void PictureWidget::loadPicture(const QModelIndex& index)
{
  auto path = mModel
    ->pictureModel()
    ->data(index, PictureModel::PictureRole::FilePathRole).toUrl().path();

  mPixmap = QPixmap(path);

  updatePicturePixmap();
}

void PictureWidget::updatePicturePixmap()
{
  if (mPixmap.isNull()) {
    return;
  }

  ui->pictureLabel->setPixmap(mPixmap.scaled(ui->pictureLabel->size(),
        Qt::KeepAspectRatio));
}
