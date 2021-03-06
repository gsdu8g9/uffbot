#ifndef VKCHOOSEPEER_H
#define VKCHOOSEPEER_H

#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QApplication>
#include <QMessageBox>

#include <QPointer>

class VkChoosePeer : public QObject
{
Q_OBJECT
QPointer<QQuickView> viewer; //QQuickView *viewer; с оберткой
QString access_token;
QString peer_id;

public:
    explicit VkChoosePeer(QObject *parent = 0);
    ~VkChoosePeer();

public slots:
    void ChoosePeer(QString token);
    QString getToken();
    void peerChoosed(QString id);
    void vkerror(QString code);

private slots:
    void easteregg();

signals:
    void setPeer(QString id);

};

#endif // VKCHOOSEPEER_H
