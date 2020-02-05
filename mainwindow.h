#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spotifywrapper.h"
#include "iftttconnector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void on_playButton_clicked();
    void on_volumeSlider_sliderReleased();
    void on_pauseButton_clicked();
    void timerFinished();

private:
    Ui::MainWindow *ui;
    SpotifyWrapper spotifyWrapper;
    IftttConnector *ifttt;
    void authenticated();
    void showInfo();
    bool ignoreVolumeUpdate;
};
#endif // MAINWINDOW_H
