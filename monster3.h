#ifndef MONSTER3_H
#define MONSTER3_H
#include"monster.h"
class playscene;

class monster3 : public monster
{
public:
    monster3(moveway *startpoint, int tagg,int hp,playscene *gamee,QString picture);
    ~monster3();
    void draw(QPainter *painter) const;
};

#endif // MONSTER3_H
