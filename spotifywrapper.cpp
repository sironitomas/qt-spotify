#include "spotifywrapper.h"
#include <QtNetworkAuth>
#include <QtCore>
#include <QtGui>

SpotifyWrapper::SpotifyWrapper(QObject *parent) : QObject(parent)
{
    auto replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    oauth2.setReplyHandler(replyHandler);
    oauth2.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    oauth2.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    oauth2.setScope("user-modify-playback-state user-read-currently-playing");
    oauth2.setClientIdentifier("a3b6f6ac59d44ef3904b72b8f2be25ac");
    oauth2.setClientIdentifierSharedKey("5860c015326b43db812feb041b31f453");

    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](
            QAbstractOAuth2::Status status) {
        if (status == QAbstractOAuth2::Status::Granted)
            emit authenticated();
    });
    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
            &QDesktopServices::openUrl);
}

void SpotifyWrapper::grant()
{
    oauth2.grant();
}

void SpotifyWrapper::skip(bool next)
{
    QString skip;
    if (next)
        skip = "next";
    else
        skip = "previous";

    QNetworkReply *reply = oauth2.post(QUrl("https://api.spotify.com/v1/me/player/" + skip));
    connect(reply, &QNetworkReply::finished, [=]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qCritical() << reply->errorString();
            return;
        }
    });
}

void SpotifyWrapper::playPause()
{
    QNetworkReply *reply = oauth2.put(QUrl("https://api.spotify.com/v1/me/player/play"));
    connect(reply, &QNetworkReply::finished, [=]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qCritical() << reply->errorString();
            return;
        }
    });
}

void SpotifyWrapper::setVolume(int volume_percent)
{
    QVariantMap params;
    QVariant percent(volume_percent);
    params.insert(QString("volume_percent"), percent);
    QString endpoint = "https://api.spotify.com/v1/me/player/volume/?volume_percent="
                       + QString::number(volume_percent);
    QNetworkReply *reply = oauth2.put(QUrl(endpoint), params);
    connect(reply, &QNetworkReply::finished, [=]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qCritical() << reply->errorString();
            return;
        }
    });
}
