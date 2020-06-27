#ifndef STAR_H
#define STAR_H
#include"tower.h"
class playscene;

class star : public tower
{
public:
    star(QPoint p, int tagg,playscene *game);
    ~star();
    int cost;
    int upcost;
    int value;
    void draw(QPainter *painter) const;
    bool upgrade;
    void up();
public slots:
    void shootWeapon();
};

#endif // STAR_H
