#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spotifywrapper.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spotifyWrapper.grant();
    connect(&spotifyWrapper, &SpotifyWrapper::authenticated,
            this, &MainWindow::authenticated);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authenticated()
{
    this->show();
}

void MainWindow::on_nextButton_clicked()
{
    spotifyWrapper.skip(true);
}

void MainWindow::on_previousButton_clicked()
{
    spotifyWrapper.skip(false);

}

void MainWindow::on_playPauseButton_clicked()
{
    spotifyWrapper.playPause();
}

void MainWindow::on_volumeSlider_sliderReleased()
{
    spotifyWrapper.setVolume(this->ui->volumeSlider->value());
}
