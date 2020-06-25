#ifndef MOVEWAY_H
#define MOVEWAY_H
#include<QPoint>
#include <QObject>
#include<QPainter>

class moveway : public QObject
{
    Q_OBJECT
public:
    //explicit moveway(QObject *parent = nullptr);
    moveway(QPoint pos);

    void setNextWayPoint(moveway  *nextPoint);
    moveway* nextWayPoint() const;
    const QPoint pos() const;
    void draw(QPainter *painter) const;

protected:
    QPoint posnow;
    moveway * nextpoint;
    QString picway;

signals:

public slots:
};

#endif // MOVEWAY_H
