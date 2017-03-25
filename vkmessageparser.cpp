#include <QString>

namespace VkMessageParser {
QString parse(QString value){
    if (value.compare("lol",Qt::CaseInsensitive)==0) return "omg";
    return "NoMESSAGE!";
}
}
