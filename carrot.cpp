#include "carrot.h"

//carrot::carrot(QObject *parent) : QObject(parent)
//{

//}
carrot::carrot(QString picway,QPoint position)
{
    pic=picway;
    pos=position;
}
void carrot::draw(QPainter *painter)
{
    QPixmap pix;
    pix.load(pic);
    pix=pix.scaled(100,100);
    painter->drawPixmap(pos,pix);
}
