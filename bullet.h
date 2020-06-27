#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include<QPainter>
#include"monster.h"
#include<QVariantAnimation>
class playscene;

class bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setcurrentpos)
public:
    //explicit bullet(QObject *parent = nullptr);
    bullet(QPoint startp, QPoint targetpoint,int damagee, int tagg,monster *targett,playscene *gamee);

    virtual ~bullet();
    virtual void draw(QPainter *painter) const;
    virtual void move();
    void setcurrentpos(QPoint pos);
    QPoint currentPos() const;
    int tag;

protected:
    const QPoint startpos;
    const QPoint targetpos;
    QPoint currentpos;
    monster * target;
    playscene *	game;
    int damage;
    static const QSize fixedSize;
//    QVariantAnimation  *animate;
signals:

public slots:
    virtual void hitTarget();
};

#endif // BULLET_H
