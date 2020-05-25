#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>

class monster : public QObject
{
    Q_OBJECT
public:
    explicit monster(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MONSTER_H