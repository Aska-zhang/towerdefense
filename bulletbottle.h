#ifndef BULLETBOTTLE_H
#define BULLETBOTTLE_H
#include"bullet.h"
class playscene;
class bulletbottle : public bullet
{
public:
    bulletbottle(QPoint startp, QPoint targetpoint,int damagee,bool upg, int tagg,monster *targett,playscene *gamee);
    ~bulletbottle();
    void draw(QPainter *painter) const;
    bool upgrade;
};

#endif // BULLETBOTTLE_H
