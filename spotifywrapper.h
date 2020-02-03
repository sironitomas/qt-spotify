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

    bool isPermanent() const;
    void setPermanent(bool value);

public slots:
    void grant();
    void skip(bool next);
    void playPause();
    void setVolume(int percentage);

signals:
    void authenticated();

private:
    QOAuth2AuthorizationCodeFlow oauth2;
    bool permanent = false;

};

#endif // SPOTIFYWRAPPER_H
