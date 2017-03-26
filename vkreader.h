#ifndef VKREADER_H
#define VKREADER_H

#include <QObject>
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDateTime>
#include <QDate>
#include <windows.h>

class VkReader : public QObject
{
Q_OBJECT

QNetworkAccessManager *messagewatchdog;
QNetworkAccessManager *datasender;
QString access_token;
QString peer_id;

//Если появится капча можно поюзать как симафор
bool isrunning=true;

//Пауза между проверками сообщения
int timeout=1000;

//Время приёма последнего сообщения, для ограничения повторений
int lastdate=0;

public:
    explicit VkReader(QObject *parent = 0);

    void log(QString log){
        emit addLog(log);
    }

    QString getToken(){
        return access_token;
    }

    QString getPeer(){
        return peer_id;
    }

    void setNetworkAccessManager(QNetworkAccessManager &mwd, QNetworkAccessManager &ds);

signals:
    void addLog(QString log);
    void choosePeer(QString token);
    void runCaptcha(QString sid,QString id,QString token);

private:
    void checkChat();

public slots:
    void setToken(QString token);
    void setPeer(QString peer);
    void restartbot();

    //Для отправки сообщений
    void sendData(QString param);
    void getResponse(QNetworkReply *reply);

private slots:
    void messagewatchdogcycle();
    //void exit();


};

#endif // VKREADER_H
