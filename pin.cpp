#include "pin.h"
#include"playscene.h"
#include"bulletpin.h"

Pin::Pin(QPoint p,int tagg, playscene *game):tower (p, tagg,game)
{
    attacking=false;
    attackrange=200;
    damage=20;
    firerate=1000;
    choose=NULL;
    pos=p;
    rotationSprite=0.0;
    thisgame=game;
    cost=100;
    upcost=160;
    value=80;
    upgrade=false;
    fireRateTimer = new QTimer(this);
    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));

}

Pin::~Pin()
{
//    delete fireRateTimer;
//    fireRateTimer = NULL;
}

void Pin::shootWeapon()
{
    bulletpin *bullets = new bulletpin(pos, choose->position(), damage,upgrade,2, choose, thisgame);
//    qDebug()<<"*";
    bullets->move();
    thisgame->addBullet(bullets);
}

void Pin::up()
{
    upgrade=true;
    damage=40;
    attackrange=300;
    value=200;
    firerate=700;
}

void Pin::draw(QPainter *painter) const
{
    painter->save();
    QPixmap pix;
    pix.load(":/res/TPin/pic3.png");
    pix=pix.scaled(100,100);
    painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);

    painter->setPen(Qt::white);
    painter->drawEllipse(pos.x()+fixedSize.width() / 2-attackrange,pos.y()+fixedSize.height() / 2-attackrange, attackrange*2, attackrange*2);


    if(upgrade)
    {
        pix.load(":/res/TPin/pic28.png");
        pix=pix.scaled(64,100);
        //painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);
        // 绘制偏转坐标,由中心+偏移=左上
        static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
        // 绘制炮塔并选择炮塔
        painter->translate(QPoint(pos.x()+fixedSize.width() / 2,pos.y()+fixedSize.height() / 2));
        painter->rotate(rotationSprite);

        painter->drawPixmap(offsetPoint.x()+20,offsetPoint.y(),pix.width(),pix.height(),pix);
        painter->setPen(Qt::red);
        painter->drawEllipse(QPoint(0,0), 5, 5);
        painter->restore();
    }
    else {
        pix.load(":/res/TPin/pic27.png");
        pix=pix.scaled(50,100);
        //painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);
        // 绘制偏转坐标,由中心+偏移=左上
        static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
        // 绘制炮塔并选择炮塔
        painter->translate(QPoint(pos.x()+fixedSize.width() / 2,pos.y()+fixedSize.height() / 2));
        painter->rotate(rotationSprite);

        painter->drawPixmap(offsetPoint.x()+25,offsetPoint.y(),pix.width(),pix.height(),pix);
        painter->setPen(Qt::red);
        painter->drawEllipse(QPoint(0,0), 5, 5);
        painter->restore();
    }

}
