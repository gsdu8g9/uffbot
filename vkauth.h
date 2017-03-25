#ifndef VKAUTH_H
#define VKAUTH_H

#include <QObject>
#include <QWebEngineView>
#include <QUrl>
#include <QUrlQuery>

class VkAuth : public QObject
{
Q_OBJECT
QWebEngineView *viewer;
QString access_token;
QVariant id=5915208;

private slots:
void checkUrl();


public:
explicit VkAuth(QObject *parent = 0);
void Auth(QWebEngineView &v);


signals:
void authcompleted(QString token);

public slots:
};

#endif // VKAUTH_H