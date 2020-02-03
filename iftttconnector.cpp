#include "iftttconnector.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

IftttConnector::IftttConnector(const QString &key, QObject *parent) : QObject(parent)
{
    ifttt_key = key;
    manager = new QNetworkAccessManager();

}

void IftttConnector::eventGet(const QString event)
{
    QNetworkRequest request;
    QString url = "https://maker.ifttt.com/trigger/" + event + "/with/key/" + ifttt_key;
    request.setUrl(QUrl(url));
    manager->get(request);
    QObject::connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }
            QString answer = reply->readAll();
            qDebug() << answer;
        }
    );
}
