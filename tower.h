#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include"monster.h"
#include<QPoint>
#include<QPainter>
#include<QTimer>
//#include<playscene.h>
class playscene;
class tower : public QObject
{
    Q_OBJECT
public:
    explicit tower(QPoint p, playscene *game);
    ~tower();

    void draw(QPainter *painter) const;
    void attackEnemy();
    void chooseEnemyForAttack(monster *m);
    void targetKilled();
    void lostSightOfEnemy();


protected:
    int attackrange;//攻击范围
    int damage;//伤害
    int HP;
    int firerate;//攻击频率
    QString picway;
    QPoint pos;
    bool attacking;
    monster *choose;//选择攻击的目标
    qreal rotationSprite;

    QTimer * fireRateTimer;

    static const QSize fixedSize;



signals:

public slots:
    void shootWeapon();
};

#endif // TOWER_H
