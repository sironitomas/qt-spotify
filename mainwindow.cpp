#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spotifywrapper.h"
#include "albumartcontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ignoreVolumeUpdate = false;

    spotifyWrapper.grant();
    connect(&spotifyWrapper, &SpotifyWrapper::authenticated,
            this, &MainWindow::authenticated);
    connect(&spotifyWrapper, &SpotifyWrapper::updatedInfo,
            this, &MainWindow::showInfo);

    ifttt = new IftttConnector("oMWyNaxm1S3VLs4OI4aqQ");
    aac = new AlbumArtContainer();
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

    // Timer is used to keep currently playing information updated
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerFinished);
    timer->start(1000);
    ignoreVolumeUpdate = false;
}

void MainWindow::showInfo()
{
    QString oldArtistName = ui->artistLabel->text();

    QStringList info = spotifyWrapper.getSongInfo();
    ui->artistLabel->setText(info.value(0));
    ui->albumLabel->setText(info.value(1));
    ui->songLabel->setText(info.value(2));
    this->adjustSize();

    if (info.value(0) != oldArtistName) {
        this->setNewScene();
    }

    if (spotifyWrapper.getDeviceName() == "-")
        ui->deviceLabel->setText("No active devices to control");
    else
        ui->deviceLabel->setText("Controlling device: " + spotifyWrapper.getDeviceName());

    int completion = spotifyWrapper.getCompletionInfo();
    ui->progressBar->setValue(completion);

    int volume_percent = spotifyWrapper.getVolumeInfo();
    if (!ignoreVolumeUpdate)
    {
        ui->volumeSlider->setValue(volume_percent);
        this->setWindowTitle("QtSpotify - Volume: " + QString::number(volume_percent) + "%");
    }
    else {
        ignoreVolumeUpdate = false;
    }

    if (spotifyWrapper.getIsActive()) {
        aac->setImage(spotifyWrapper.getArt(), info.value(1));
        aac->show();
        if (spotifyWrapper.getIsPlaying()) {
            ui->playButton->setEnabled(false);
            ui->pauseButton->setEnabled(true);
        }
        else {
            ui->playButton->setEnabled(true);
            ui->pauseButton->setEnabled(false);
        }
        ui->volumeSlider->setEnabled(true);
        ui->nextButton->setEnabled(true);
        ui->previousButton->setEnabled(true);
    }
    else {
        aac->hide();
        ui->volumeSlider->setEnabled(false);
        ui->playButton->setEnabled(false);
        ui->pauseButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
        ui->previousButton->setEnabled(false);
    }
}

void MainWindow::setNewScene()
{
    ifttt->eventGet("random_colors");
}

void MainWindow::on_nextButton_clicked()
{
    spotifyWrapper.skip(true);
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
    int value = this->ui->volumeSlider->value();
    spotifyWrapper.setVolume(value);
    this->setWindowTitle("QtSpotify - Volume: " + QString::number(value) + "%");
    // Workaround to avoid strange volume slider behaviour
    ignoreVolumeUpdate = true;
}

void MainWindow::timerFinished()
{
    spotifyWrapper.fillUpdatedInfo();
}



