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
