#include "guiwindow.h"
#include "vkreader.h"
#include "vkauth.h"
#include "vkchoosepeer.h"
#include "vkcaptcha.h"
#include <QApplication>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QSslSocket>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!QSslSocket::supportsSsl()){
        //Ошибка, нет библиотек openssl. Нахуя он нужен, если ключи шифрования у ФСБ я не знаю, но можно сделать так
        //Qt компилирует с OpenSSL из коробки, но из за бюрократии не может сам кидать dll к exe файлу
        //Заходим на https://indy.fulgan.com/SSL/
        //Ищем ревизию openssl по строке, возращаемой через QSslSocket::sslLibraryBuildVersionString()
        //кидаем libeay32.dll и ssleay32.dll из архива к бинарнику
        //Следует качать ревизию, соответствующую разрядности компилятора, в нашем случае MSVC2015_64bit
        QMessageBox msg;
        msg.setText("ERROR! NEED OpenSSL installed, project compiled with "+QSslSocket::sslLibraryBuildVersionString()+" so you need add some dll's.");
        msg.exec();
        qDebug()<<"Проверь main функцию, я знаю как убрать эту поебень и оставил комментарий";
        return a.exit(0);
    }

    GuiWindow w;
    VkReader vk;


    QObject::connect(&vk,SIGNAL(addLog(QString)),&w,SLOT(addLog(QString)));

    w.addLog("Вас приветствует УФФБОТ\nДля продолжения работы войдите в ВК");

    QWebEngineView webview;
    //webview.page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    webview.setWindowTitle("Вход в вк");
    VkAuth vkauth;
    vkauth.Auth(webview);

    QObject::connect(&vkauth,SIGNAL(authcompleted(QString)),&vk,SLOT(setToken(QString)));

    VkChoosePeer vkpeer;
    QQuickView viewer;
    vkpeer.setView(viewer);
    viewer.rootContext()->setContextProperty("backEnd", &vkpeer);
    QObject::connect(&vk,SIGNAL(choosePeer(QString)),&vkpeer,SLOT(ChoosePeer(QString)));
    QObject::connect(&vkpeer,SIGNAL(setPeer(QString)),&vk,SLOT(setPeer(QString)));
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    VkCaptcha vkcaptcha;
    QObject::connect(&vk,SIGNAL(runCaptcha(QString,QString,QString)),&vkcaptcha,SLOT(runCaptcha(QString,QString,QString)));
    QObject::connect(&vkcaptcha,SIGNAL(log(QString)),&w,SLOT(addLog(QString)));
    QObject::connect(&vkcaptcha,SIGNAL(sendData(QString)),&vk,SLOT(sendData(QString)));
    QObject::connect(&vkcaptcha,SIGNAL(restartbot()),&vk,SLOT(restartbot()));


    return a.exec();

}
