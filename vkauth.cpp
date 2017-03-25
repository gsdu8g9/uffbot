#include "vkauth.h"

VkAuth::VkAuth(QObject *parent) : QObject(parent){

}

void VkAuth::Auth(QWebEngineView &v){
viewer=&v;
connect(viewer,SIGNAL(loadFinished(bool)),this,SLOT(checkUrl()));

viewer->setWindowFlags(Qt::WindowTitleHint);
viewer->setUrl(QUrl(QString("http://oauth.vk.com/authorize?client_id="+id.toString()+"redirect_uri=https://oauth.vk.com/blank.html&response_type=token&scope=messages&display=mobile")));
viewer->show();
}

void VkAuth::checkUrl(){
QUrl url(viewer->url().toString());
if(url.toString().contains("access_token")){
viewer->setHtml("OK");
url = url.toString().replace("#", "?");
QUrlQuery query(url);
access_token=QString(query.queryItemValue("access_token"));
viewer->hide();
emit authcompleted(access_token);
}
}
