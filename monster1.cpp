#include "monster1.h"
static const int Health_Bar_Width = 50;
monster1::monster1(moveway *startpoint, int tagg,int hp,playscene *gamee,QString picture)
    :monster (startpoint,tagg,hp, gamee,picture)
{
//    maxHP=300;
//    currentHP=300;
    speed=1.5;
}
monster1::~monster1()
{
//    attackedtowerslist.clear();
//    destinationpoint=NULL;
//    game=NULL;
}

void monster1::draw(QPainter *painter) const
{
    if (!alive)
        return;

    painter->save();

    QPoint healthBarPoint = pos + QPoint(-Health_Bar_Width / 2 - 5, -fixedSize.height() / 3-8);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)currentHP / maxHP * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);



    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
    painter->translate(pos);
//    painter->rotate(rotationSprite);
    // 绘制敌人
    //painter->drawPixmap(offsetPoint, m_sprite);

    QPixmap pix;
//    pix.load(":/res/Monsters1/pic2.png");
    pix.load(pic);
    pix.scaled(160,160);
    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),pix.width()*1.6,pix.height()*1.59,pix);
//    QPixmap pix;
//    pix.load(pic);
//    pix.load(":/res/Monsters1/pic1.png");
//    pix.scaled(160,160);
//    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),pix.width()*1.6,pix.height()*1.59,pix);

    painter->restore();
}
