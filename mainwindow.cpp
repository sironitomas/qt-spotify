#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spotifywrapper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spotifyWrapper.grant();
    connect(&spotifyWrapper, &SpotifyWrapper::authenticated,
            this, &MainWindow::authenticated);
    connect(&spotifyWrapper, &SpotifyWrapper::updatedInfo,
            this, &MainWindow::showInfo);
    ifttt = new IftttConnector("d_HNRJwe0GdzNiVEJJyWCE");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authenticated()
{
    // Window will only be seen if user authenticated
    this->show();
    spotifyWrapper.fillUpdatedInfo();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerFinished);
    timer->start(1000);
}

void MainWindow::showInfo()
{
    QStringList info = spotifyWrapper.getSongInfo();
    ui->artistLabel->setText(info.value(0));
    ui->albumLabel->setText(info.value(1));
    ui->songLabel->setText(info.value(2));

    int volume_percent = spotifyWrapper.getVolumeInfo();
    ui->volumeSlider->setValue(volume_percent);
}

void MainWindow::on_nextButton_clicked()
{
    spotifyWrapper.skip(true);
    spotifyWrapper.fillUpdatedInfo();
//    ifttt->eventGet("rock");
}

void MainWindow::on_previousButton_clicked()
{
    spotifyWrapper.skip(false);
}

void MainWindow::on_playButton_clicked()
{
    spotifyWrapper.play();
}

void MainWindow::on_pauseButton_clicked()
{
    spotifyWrapper.pause();
}

void MainWindow::on_volumeSlider_sliderReleased()
{
    spotifyWrapper.setVolume(this->ui->volumeSlider->value());
}

void MainWindow::timerFinished()
{
    spotifyWrapper.fillUpdatedInfo();
}


