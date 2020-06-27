#ifndef MONSTER2_H
#define MONSTER2_H
#include"monster.h"
class playscene;


class monster2 : public monster
{
public:
    monster2(moveway *startpoint,int tagg,int hp, playscene *gamee,QString picture);
    ~monster2();
    void draw(QPainter *painter) const;
};

#endif // MONSTER2_H
