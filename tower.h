#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include"monster.h"
#include<QPoint>
#include<QPainter>
#include<QTimer>
//#include<playscene.h>
#include"bullet.h"
class playscene;
class tower : public QObject
{
    Q_OBJECT
public:
    explicit tower(QPoint p, int tagg,playscene *game);
    virtual ~tower();

    virtual void draw(QPainter *painter) const;
    void attackEnemy();
    void chooseEnemyForAttack(monster *m);
    void targetKilled();
    void lostSightOfEnemy();
    virtual void checkEnemyInRange();
    void damageEnemy();
    void removeBullet();
    inline QPoint position()const{return pos;}
    virtual void upgrade(){};

    int gettag(){return tag;}

protected:
    int attackrange;//攻击范围
    int damage;//伤害
//    int HP;
    int firerate;//攻击频率
    int tag;
    QString picway;
    QPoint pos;
    bool attacking;
    monster *choose;//选择攻击的目标
    qreal rotationSprite;
    playscene * thisgame;

    QTimer * fireRateTimer;

    static const QSize fixedSize;



signals:

public slots:
    virtual void shootWeapon();
};

#endif // TOWER_H
