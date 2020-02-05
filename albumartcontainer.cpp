#include "albumartcontainer.h"
#include "ui_albumartcontainer.h"
#include <QPainter>

AlbumArtContainer::AlbumArtContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumArtContainer)
{
    ui->setupUi(this);
}

void AlbumArtContainer::setImage(QImage art)
{
    albumArt = art;
    this->update();
}

AlbumArtContainer::~AlbumArtContainer()
{
    delete ui;
}

void AlbumArtContainer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    this->adjustSize();
    painter.drawImage(QPoint(0,0), albumArt);
}
