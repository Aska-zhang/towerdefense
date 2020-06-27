#ifndef BULLETPIN_H
#define BULLETPIN_H
#include"bullet.h"
class playscene;

class bulletpin : public bullet
{
public:
    bulletpin(QPoint startp, QPoint targetpoint,int damagee, bool upg,int tagg,monster *targett,playscene *gamee);
    ~bulletpin();
    void draw(QPainter *painter) const;
    bool upgrade;
};

#endif // BULLETPIN_H
