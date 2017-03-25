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
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
