#ifndef SPOTIFYWRAPPER_H
#define SPOTIFYWRAPPER_H

#include <QOAuth2AuthorizationCodeFlow>
#include <QtNetwork>
#include <QObject>

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
    int getVolumeInfo();
    bool getIsPlaying();

signals:
    void authenticated();
    void updatedInfo();

private:
    QOAuth2AuthorizationCodeFlow oauth2;
    bool permanent = false;
    QString artistName;
    QString albumName;
    QString songName;
    int volumePercent;
    bool isPlaying;
};

#endif // SPOTIFYWRAPPER_H
