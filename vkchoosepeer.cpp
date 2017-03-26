#include "vkchoosepeer.h"

VkChoosePeer::VkChoosePeer(QObject *parent) : QObject(parent){
    viewer= new QQuickView;
    viewer->rootContext()->setContextProperty("backEnd", this);
    connect(viewer,SIGNAL(closing(QQuickCloseEvent*)),this,SLOT(easteregg()));
}


void VkChoosePeer::ChoosePeer(QString token){
    access_token=token;
    viewer->setSource(QUrl("qrc:/choosechat.qml"));
    viewer->show();
}

QString VkChoosePeer::getToken(){
    return access_token;
}

void VkChoosePeer::peerChoosed(QString id){
    peer_id=id;
    viewer->close();
    emit setPeer(id);
}

void VkChoosePeer::vkerror(QString code){
    QMessageBox msg;
    msg.setText("API VK вернуло ошибку "+code+". Программа будет закрыта...");

}

void VkChoosePeer::easteregg(){
    if(!peer_id.isEmpty()) return;
    QMessageBox msg;
    msg.setText("Хули ты сделал, хули ты крестиками вымазался, мудак блядь?(вы нашли пасхалку)");
    msg.exec();
    qApp->quit();
}

