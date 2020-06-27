#include "monster.h"
#include"tower.h"
#include"collisioncheck.h"
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include<QObject>
#include"playscene.h"
//monster::monster(QObject *parent) : QObject(parent)
//{

//}
static const int Health_Bar_Width = 50;

const QSize monster::fixedSize(100, 100);
monster::monster(moveway *startpoint,int tagg, int hp,playscene *gamee,QString picture):
    alive(false),maxHP(hp),currentHP(hp),speed(2.0),rotationSprite(0.0),pic(picture)
  ,pos(startpoint->pos()),destinationpoint(startpoint->nextWayPoint()),game(gamee),tag(tagg)

{

}
monster::~monster()
{
    attackedtowerslist.clear();
    destinationpoint=NULL;
    game=NULL;
}
void monster::becomealive()
{
    alive=true;
}

QPoint monster::position() const
{
    return pos;
}
void monster::getAttacked(tower *attacker)
{
    attackedtowerslist.push_back(attacker);
}
void monster::getDamage(int damage)
{
    game->audioPlayer->playSound(bottle);
    currentHP -= damage;

    // 阵亡,需要移除
    if (currentHP <= 0)
    {
        game->audioPlayer->playSound(Fat142);
        game->awardGold(40);
        getRemoved();
    }
}

void monster::getRemoved()
{
    if (attackedtowerslist.empty())
        return;

    foreach (tower *attacker, attackedtowerslist)
        attacker->targetKilled();
//     通知game,此敌人已经阵亡
    game->removedEnemy(this);
}

void monster::gotLostSight(tower *attacker)
{
    attackedtowerslist.removeOne(attacker);
}


void monster::draw(QPainter *painter) const
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
//    pix.load(":/res/Monsters1/pic1.png");
    pix.load(pic);
    pix.scaled(160,160);
    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),pix.width()*1.6,pix.height()*1.59,pix);

    painter->restore();
}
void monster::move()
{
    if (!alive)
        return;

    if (collisionWithCircle(pos, 1,destinationpoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (destinationpoint->nextWayPoint())
        {
            // 还有下一个航点
            pos = destinationpoint->pos();
            destinationpoint = destinationpoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
           game->getHpDamage();
            game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = destinationpoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = speed;
    QVector2D normalized(targetPoint - pos);
    normalized.normalize();
    pos =pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}
