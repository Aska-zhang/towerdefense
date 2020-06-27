#ifndef BOTTLE_H
#define BOTTLE_H

#include <QObject>
#include"tower.h"

class playscene;
class Bottle : public tower
{
public:
    Bottle(QPoint p, int tagg,playscene *game);
    ~Bottle();
    int cost;
    int upcost;
    int value;
    void draw(QPainter *painter) const;
    bool upgrade;
    void up();
public slots:
    void shootWeapon();
};

#endif // BOTTLE_H
