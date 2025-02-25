#ifndef SPOTIFYWRAPPER_H
#define SPOTIFYWRAPPER_H

#include <QOAuth2AuthorizationCodeFlow>
#include <QtNetwork>
#include <QObject>
#include <QImage>

class SpotifyWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyWrapper(QObject *parent = nullptr);
    void grant();
    void skip(bool);
    void play();
    void pause();
    void setVolume(int);
    void fillUpdatedInfo();
    QStringList getSongInfo();
    QString getDeviceName();
    int getVolumeInfo();
    int getCompletionInfo();
    bool getIsPlaying();
    bool getIsActive();
    QImage getArt();

signals:
    void authenticated();
    void updatedInfo();

private:
    QOAuth2AuthorizationCodeFlow oauth2;
    bool permanent = false;
    QString artistName;
    QString albumName;
    QString songName;
    QString deviceName;
    int volumePercent;
    bool isPlaying;
    bool isActive;
    bool newArt;
    int completion;
    QUrl artUri;
    QImage art;
};

#endif // SPOTIFYWRAPPER_H
