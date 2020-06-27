#ifndef PIN_H
#define PIN_H
#include"tower.h"
class playscene;

class Pin : public tower
{
public:
    Pin(QPoint p, int tagg,playscene *game);
    ~Pin();
    int cost;
    int upcost;
    int value;
    void draw(QPainter *painter) const;
    bool upgrade;
    void up();
public slots:
    void shootWeapon();
};

#endif // PIN_H
