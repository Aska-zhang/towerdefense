#include "bullet.h"
#include"playscene.h"
#include <QPainter>
#include <QPropertyAnimation>
#include<QDebug>
//bullet::bullet(QObject *parent) : QObject(parent)
//{

//}
const QSize bullet::fixedSize(10, 10);

bullet::bullet(QPoint startp, QPoint targetpoint,int damagee, monster *targett,playscene *gamee)
    :startpos(startp),targetpos(targetpoint),currentpos(startp),target(targett),game(gamee),damage(damagee)
    ,animate(new QVariantAnimation)
{
//qDebug()<<targetpos.x()<<" "<<targetpoint.y()<<endl;
//qDebug()<<targett->position().x();
}

void bullet::draw(QPainter *painter) const
{
    QPixmap pix;
    pix.load(":/res/TBottle/pic6.png");
    pix.scaled(100,100);
    painter->drawPixmap(currentpos.x(),currentpos.y(),pix.width()*1.6,pix.height()*1.6,pix);
}

void bullet::move()
{

//    animate->setDuration(200);
//    animate->setStartValue(startpos);
//    animate->setEndValue(targetpos);
//    connect(animate, &QVariantAnimation::valueChanged, [=](const QVariant &value){
//                qDebug()<<value;
//                QTransform t;
//                t.rotate(value.toReal());
//                  this->draw();
//                  setcurrentpos(animate->currentValue().toPoint());
//                setPixmap(pixmap.transformed(t));
//            });
//    animate->start();
    // 100毫秒内击中敌人
    static const int duration = 600;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "currentpos");
    animation->setDuration(duration);
    animation->setStartValue(startpos);
    animation->setEndValue(targetpos);
    animation->setEasingCurve(QEasingCurve::Linear);
    connect(animation, &QPropertyAnimation::valueChanged, [=](){
        qreal movementSpeed = 10;
        QVector2D normalized(targetpos - currentPos());
        normalized.normalize();
        setcurrentpos( currentPos() + normalized.toPoint() * movementSpeed);
//            setcurrentpos(animate->currentValue().toPoint());
            qDebug()<<"current"<<currentPos().x()<<"target"<<targetpos.x();
    });

    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}
void bullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (game->enemyList().indexOf(target) != -1)
        target->getDamage(damage);
    game->removedBullet(this);
}

void bullet::setcurrentpos(QPoint pos)
{
    currentpos = pos;
}

QPoint bullet::currentPos() const
{
    return currentpos;
}
