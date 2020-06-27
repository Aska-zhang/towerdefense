#include "star.h"
#include"playscene.h"
#include"bulletstar.h"

star::star(QPoint p,int tagg, playscene *game):tower (p,tagg,game)
{
    attacking=false;
    attackrange=200;
    damage=25;
    firerate=1000;
    choose=nullptr;
    pos=p;
    rotationSprite=0.0;
    thisgame=game;
    cost=220;
    upcost=400;
    value=176;
    upgrade=false;
    fireRateTimer = new QTimer(this);
    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

star::~star()
{
//    delete fireRateTimer;
//    fireRateTimer = NULL;
}

void star::shootWeapon()
{
    bulletstar *bullets = new bulletstar(pos, choose->position(), damage,upgrade,3, choose, thisgame);
//    qDebug()<<"*";
    bullets->move();
    thisgame->addBullet(bullets);
}

void star::up()
{
    upgrade=true;
    damage=50;
    attackrange=300;
    value=496;
    firerate=600;
}

void star::draw(QPainter *painter) const
{
    painter->save();
    QPixmap pix;
    pix.load(":/res/TBlueStar/pic51.png");
    pix=pix.scaled(100,100);
    painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);

    painter->setPen(Qt::white);
    painter->drawEllipse(pos.x()+fixedSize.width() / 2-attackrange,pos.y()+fixedSize.height() / 2-attackrange, attackrange*2, attackrange*2);


    if(upgrade)
    {
        pix.load(":/res/TBlueStar/pic53.png");
        pix=pix.scaled(100,100);
        //painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);
        // 绘制偏转坐标,由中心+偏移=左上
        static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
        // 绘制炮塔并选择炮塔
        painter->translate(QPoint(pos.x()+fixedSize.width() / 2,pos.y()+fixedSize.height() / 2));
        painter->rotate(rotationSprite);

        painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),pix.width(),pix.height(),pix);
        painter->setPen(Qt::red);
        painter->drawEllipse(QPoint(0,0), 5, 5);
        painter->restore();
    }
    else {
        pix.load(":/res/TBlueStar/pic66.png");
        pix=pix.scaled(70,70);
        //painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);
        // 绘制偏转坐标,由中心+偏移=左上
        static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
        // 绘制炮塔并选择炮塔
        painter->translate(QPoint(pos.x()+fixedSize.width() / 2,pos.y()+fixedSize.height() / 2));
        painter->rotate(rotationSprite);

        painter->drawPixmap(offsetPoint.x()+15,offsetPoint.y()+15,pix.width(),pix.height(),pix);
        painter->setPen(Qt::red);
        painter->drawEllipse(QPoint(0,0), 5, 5);
        painter->restore();
    }

}
