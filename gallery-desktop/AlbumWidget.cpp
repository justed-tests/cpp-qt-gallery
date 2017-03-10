#include "AlbumWidget.h"
#include "ui_AlbumWidget.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget)
{
    ui->setupUi(this);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}
