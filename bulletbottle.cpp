#include "bulletbottle.h"

bulletbottle::bulletbottle(QPoint startp, QPoint targetpoint,int damagee, bool upg,int tagg,monster *targett,playscene *gamee)
    :bullet (startp, targetpoint,damagee, tagg,targett,gamee),upgrade(upg)
{

}
bulletbottle::~bulletbottle()
{
//    target=nullptr;
}
void bulletbottle::draw(QPainter *painter) const
{
    if(upgrade)
    {
        QPixmap pix;
        pix.load(":/res/TBottle/pic8.png");
        pix.scaled(100,100);
        painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width()*1.6,pix.height()*1.6,pix);
    }
    else {
        QPixmap pix;
        pix.load(":/res/TBottle/pic6.png");
        pix.scaled(100,100);
        painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width()*1.6,pix.height()*1.6,pix);
    }

}
