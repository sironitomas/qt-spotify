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

public slots:
    void grant();
    void skip(bool);
    void playPause();
    void setVolume(int);

signals:
    void authenticated();

private:
    QOAuth2AuthorizationCodeFlow oauth2;
    bool permanent = false;

};

#endif // SPOTIFYWRAPPER_H
