#ifndef BULLETSTAR_H
#define BULLETSTAR_H
#include"bullet.h"
class playscene;

class bulletstar : public bullet
{
public:
    bulletstar(QPoint startp, QPoint targetpoint,int damagee, bool upg,int tagg,monster *targett,playscene *gamee);
    ~bulletstar();
    void draw(QPainter *painter) const;
    bool upgrade;
public slots:
    void hitTarget();
};

#endif // BULLETSTAR_H
