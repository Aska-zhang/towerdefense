#include "moveway.h"
#include<QPoint>

//moveway::moveway(QObject *parent) : QObject(parent)
//{

//}
moveway::moveway(QPoint pos):posnow(pos),nextpoint(nullptr)
{

}
void moveway::setNextWayPoint(moveway  *nextPoint)
{
    nextpoint=nextPoint;
}
moveway* moveway::nextWayPoint() const
{
    return nextpoint;
}

const QPoint moveway::pos() const
{
    return  posnow;
}
void moveway::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::green);
    painter->drawEllipse(posnow, 6, 6);
    painter->drawEllipse(posnow, 2, 2);

    if (nextpoint)
        painter->drawLine(posnow, nextpoint->posnow);
    painter->restore();
}
