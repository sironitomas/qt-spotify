#ifndef ALBUMARTCONTAINER_H
#define ALBUMARTCONTAINER_H

#include <QWidget>

namespace Ui {
class AlbumArtContainer;
}

class AlbumArtContainer : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumArtContainer(QWidget *parent = nullptr);
    void setImage(QImage);
    ~AlbumArtContainer();


private slots:
    void paintEvent(QPaintEvent *);
private:
    Ui::AlbumArtContainer *ui;
    QImage albumArt;
};

#endif // ALBUMARTCONTAINER_H
