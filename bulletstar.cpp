#include "bulletstar.h"
#include"playscene.h"

bulletstar::bulletstar(QPoint startp, QPoint targetpoint,int damagee, bool upg,int tagg,monster *targett,playscene *gamee)
    :bullet (startp,targetpoint,damagee, tagg,targett,gamee),upgrade(upg)
{

}

bulletstar::~bulletstar()
{

}

void bulletstar::draw(QPainter *painter) const
{
    if(upgrade)
    {
        QPixmap pix;
        pix.load(":/res/TBlueStar/pic37.png");
        pix=pix.scaled(100,100);
        painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width(),pix.height(),pix);
    }
    else {
        QPixmap pix;
        pix.load(":/res/TBlueStar/pic38.png");
        pix=pix.scaled(50,50);
        painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width(),pix.height(),pix);
    }

}

void bulletstar::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (game->enemyList().indexOf(target) != -1)
    {    target->getDamage(damage);
        target->changespped(target->getspeed()*0.8);
    }

//    foreach(monster* mo,game->enemyList())
//    {

//    }
    game->removedBullet(this);
}
