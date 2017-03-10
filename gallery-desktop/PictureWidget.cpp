#include "PictureWidget.h"
#include "ui_PictureWidget.h"

PictureWidget::PictureWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PictureWidget),
  mModel(nullptr),
  mSelectionModel(nullptr)
{
  ui->setupUi(this);
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

void PictureWidget::loadPicture(const QItemSelection& selected)
{
}

void PictureWidget::updatePicturePixmap()
{
  if (mPixmap.isNull()) {
    return;
  }

  ui->pictureLabel->setPixmap(mPixmap.scaled(ui->pictureLabel->size(),
        Qt::KeepAspectRatio));
}
