#include "tower.h"
#include<QTimer>
#include<QPainter>
#include"playscene.h"
#include <QColor>
#include <QVector2D>
#include <QtMath>
#include"bullet.h"
#include"collisioncheck.h"
#include<QDebug>

const QSize tower::fixedSize(100, 100);
tower::tower(QPoint p,int tagg, playscene *game)
{
    attacking=false;
    attackrange=200;
    damage=10;
    firerate=1000;
    choose=NULL;
    pos=p;
    rotationSprite=0.0;
    thisgame=game;
    tag=tagg;

    fireRateTimer = new QTimer(this);
    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));


}

tower::~tower()
{
    delete fireRateTimer;
    fireRateTimer = nullptr;
}

void tower::draw(QPainter *painter) const
{
    painter->save();
    QPixmap pix;
    pix.load(":/res/TBottle/TBottle-dz.png");
    pix=pix.scaled(100,100);
    painter->drawPixmap(pos.x(),pos.y(),pix.width(),pix.height(),pix);

    painter->setPen(Qt::white);
    painter->drawEllipse(pos.x()+fixedSize.width() / 2-attackrange,pos.y()+fixedSize.height() / 2-attackrange, attackrange*2, attackrange*2);


    pix.load(":/res/TBottle/pic28.png");
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
void tower::shootWeapon()
{
    bullet *bullets = new bullet(pos, choose->position(), damage,0, choose, thisgame);
    qDebug()<<"*";
    bullets->move();
    thisgame->addBullet(bullets);
}
void tower::attackEnemy()
{
//    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
    fireRateTimer->start(firerate);
}
void tower::chooseEnemyForAttack(monster *m)
{
    choose = m;
    attackEnemy();
    choose->getAttacked(this);
}
void tower::targetKilled()
{
    if (choose)
        choose = NULL;

//    fireRateTimer->stop();
    delete fireRateTimer;
    fireRateTimer = new QTimer(this);
    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));

//    rotationSprite = 0.0;
//    checkEnemyInRange();
}
void tower::lostSightOfEnemy()
{
    //choose->gotLostSight(this);
    if (choose)
        choose = NULL;

//    fireRateTimer->stop();
    delete fireRateTimer;
    fireRateTimer = new QTimer(this);
    connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
//    rotationSprite = 0.0;
//    checkEnemyInRange();
}

void tower::checkEnemyInRange()
{
    if (choose)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(choose->position() - pos);
        normalized.normalize();
        rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;


        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(pos, attackrange, choose->position(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<monster *> enemyList = thisgame->enemyList();
        foreach (monster *enemy, enemyList)
        {
            //if (collisionWithCircle(pos, attackrange, enemy->position(), 1))
            if(collisionWithCircle(QPoint(pos.x()+fixedSize.width() / 2,pos.y()+fixedSize.height() / 2),attackrange, enemy->position(), 1))
            {
//                fireRateTimer = new QTimer(this);
//                connect(fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}
