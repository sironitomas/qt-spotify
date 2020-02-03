#ifndef IFTTTCONNECTOR_H
#define IFTTTCONNECTOR_H

#include <QObject>
#include <QNetworkAccessManager>


class IftttConnector : public QObject
{
    Q_OBJECT
public:
    explicit IftttConnector(const QString &clientIdentifier, QObject *parent = nullptr);
    void eventGet(const QString event);

signals:

private:
    QNetworkAccessManager *manager;
    QString ifttt_key;

};

#endif // IFTTTCONNECTOR_H
