#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <spotifywrapper.h>

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

    void on_playPauseButton_clicked();

    void on_horizontalSlider_sliderReleased();

private:
    Ui::MainWindow *ui;
    SpotifyWrapper spotifyWrapper;
    void authenticated();
};
#endif // MAINWINDOW_H
