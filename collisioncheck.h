#ifndef COLLISIONCHECK_H
#define COLLISIONCHECK_H


#include <QtMath>
#include<QPoint>

inline bool collisionWithCircle(QPoint point1, int r1, QPoint point2, int r2)
{
    const int xdif = point1.x() - point2.x();
    const int ydif = point1.y() - point2.y();
    const int distance = qSqrt(xdif * xdif + ydif * ydif);

    if (distance <= r1 + r2)
        return true;

    return false;
}

#endif // COLLISIONCHECK_H
