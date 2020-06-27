#ifndef MONSTER1_H
#define MONSTER1_H
#include"monster.h"
class playscene;


class monster1 : public monster
{
public:
    monster1(moveway *startpoint,int tagg,int hp, playscene *gamee,QString picture);
    ~monster1();
    void draw(QPainter *painter) const;
};

#endif // MONSTER1_H
