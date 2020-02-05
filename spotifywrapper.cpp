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
    oauth2.setScope("user-modify-playback-state user-read-playback-state user-read-currently-playing");
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

void SpotifyWrapper::play()
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

void SpotifyWrapper::pause()
{
    QNetworkReply *reply = oauth2.put(QUrl("https://api.spotify.com/v1/me/player/pause"));
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
    QString endpoint = "https://api.spotify.com/v1/me/player/volume/?volume_percent="
                       + QString::number(volume_percent);
    QNetworkReply *reply = oauth2.put(QUrl(endpoint));
    connect(reply, &QNetworkReply::finished, [=]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qCritical() << reply->errorString();
            return;
        }
    });
}

void SpotifyWrapper::fillUpdatedInfo()
{
    QNetworkReply *reply = oauth2.get(QUrl("https://api.spotify.com/v1/me/player?market=AR"));
    connect(reply, &QNetworkReply::finished, [=]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qCritical() << reply->errorString();
            return;
        }
        else {
            const auto json = reply->readAll();
            const auto document = QJsonDocument::fromJson(json);
            Q_ASSERT(document.isObject());
            const auto rootObject = document.object();

            isPlaying = rootObject.value("is_playing").toBool();
            double progress = rootObject.value("progress_ms").toDouble();

            const auto deviceValue = rootObject.value("device");
            const auto deviceObject = deviceValue.toObject();
            volumePercent = deviceObject.value("volume_percent").toInt();


            const auto itemValue = rootObject.value("item");
            const auto itemObject = itemValue.toObject();
            double duration = itemObject.value("duration_ms").toDouble();
            songName = itemObject.value("name").toString();

            const auto albumValue = itemObject.value("album");
            const auto albumObject = albumValue.toObject();
            albumName = albumObject.value("name").toString();

            const auto artistsValue = itemObject.value("artists");
            const auto artistsArray = artistsValue.toArray();
            const auto mainArtistValue = artistsArray.first();
            const auto mainArtistObject = mainArtistValue.toObject();
            artistName = mainArtistObject.value("name").toString();

            completion = (int)((progress/duration)*1000);
            emit updatedInfo();
        }
    });
}

QStringList SpotifyWrapper::getSongInfo() {
    QStringList info;
    info.append(artistName);
    info.append(albumName);
    info.append(songName);
    return info;
}

int SpotifyWrapper::getVolumeInfo() {
    return volumePercent;
}

int SpotifyWrapper::getCompletionInfo() {
    return completion;
}

bool SpotifyWrapper::getIsPlaying() {
    return isPlaying;
}

