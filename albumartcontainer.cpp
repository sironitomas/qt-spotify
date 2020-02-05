#include "albumartcontainer.h"
#include "ui_albumartcontainer.h"
#include <QPainter>

AlbumArtContainer::AlbumArtContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumArtContainer)
{
    ui->setupUi(this);
}

void AlbumArtContainer::setImage(QImage art, QString name)
{
    albumArt = art;
    this->setFixedWidth(albumArt.width());
    this->setFixedHeight(albumArt.height());
    this->setWindowTitle(name);
    this->update();
}

AlbumArtContainer::~AlbumArtContainer()
{
    delete ui;
}

void AlbumArtContainer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), albumArt);
}
