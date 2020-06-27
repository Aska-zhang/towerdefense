#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QPoint>
#include "moveway.h"
#include<QPainter>
class tower;

class playscene;
class monster : public QObject
{
    Q_OBJECT
public:
    //explicit monster(QObject *parent = nullptr);
    explicit monster(moveway *startpoint,int tagg,int hp, playscene *gamee,QString picture);
    virtual ~monster();
    virtual void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(tower *attacker);
    void gotLostSight(tower *attacker);
    QPoint position() const;
    int tag;
    void changespped(qreal s){speed=s;}
    qreal getspeed(){return speed;}


protected:
    int maxHP;
    int currentHP;
    bool alive;
    qreal speed;
    qreal rotationSprite;
    QPoint pos;//用于表示怪的中心
    moveway * destinationpoint;
    playscene * game;
    QList<tower *> attackedtowerslist;
    QString pic;
    static const QSize fixedSize;


signals:

public slots:
    void becomealive();
};

#endif // MONSTER_H
