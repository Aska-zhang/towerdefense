#include "tower.h"
#include<QTimer>
#include<QPainter>
#include"playscene.h"
#include <QColor>
#include <QVector2D>
#include <QtMath>

const QSize tower::fixedSize(100, 100);
tower::tower(QPoint p, playscene *game)
{
    attacking=false;
    attackrange=100;
    damage=10;
    firerate=1000;
    choose=NULL;
    pos=p;
    rotationSprite=0.0;

    fireRateTimer = new QTimer(this);
        connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));


}

tower::~tower()
{
    delete fireRateTimer;
    fireRateTimer = NULL;
}

void tower::draw(QPainter *painter) const
{
    painter->save();
    QPixmap pix;
    pix.load(":/res/TBottle/TBottle-dz.png");
    pix.scaled(100,100);
    painter->drawPixmap(pos.x(),pos.y(),pix.width()*1.6,pix.height()*1.6,pix);

    pix.load(":/res/TBottle/pic25.png");
    pix.scaled(160,160);
    //painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);
    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(QPoint(pos.x()+fixedSize.width() / 2+33,pos.y()+fixedSize.height() / 2-2));
    painter->rotate(rotationSprite);
    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),pix.width()*1.6,pix.height()*1.6,pix);
    painter->restore();

}
void tower::shootWeapon()
{

}
void tower::attackEnemy()
{
    fireRateTimer->start(firerate);
}
void tower::chooseEnemyForAttack(monster *m)
{
    choose = m;
    attackEnemy();
    //choose->getAttacked(this);
}
void tower::targetKilled()
{
    if (choose)
        choose = NULL;

    fireRateTimer->stop();
    rotationSprite = 0.0;
}
void tower::lostSightOfEnemy()
{
    //choose->gotLostSight(this);
    if (choose)
        choose = NULL;

    fireRateTimer->stop();
    rotationSprite = 0.0;
}
