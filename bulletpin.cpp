#include "bulletpin.h"
#include"playscene.h"
bulletpin::bulletpin(QPoint startp, QPoint targetpoint,int damagee, bool upg,int tagg,monster *targett,playscene *gamee)
    :bullet (startp,targetpoint,damagee, tagg,targett,gamee),upgrade(upg)
{

}

bulletpin::~bulletpin()
{

}

void bulletpin::draw(QPainter *painter) const
{
    if(upgrade)
    {
        QPixmap pix;
        pix.load(":/res/TPin/pic26.png");
//        pix=pix.scaled(100,100);
        painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width()*1.5,pix.height()*1.5,pix);
    }
    else {
        QPixmap pix;
        pix.load(":/res/TPin/pic15.png");
//        pix=pix.scaled(40,40);
        painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width(),pix.height(),pix);
    }

}
