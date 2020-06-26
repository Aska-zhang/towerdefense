#ifndef CARROT_H
#define CARROT_H

#include <QObject>
#include<QPainter>

class carrot : public QObject
{
    Q_OBJECT
public:
//    explicit carrot(QObject *parent = nullptr);
    carrot(QString picway,QPoint position);
    void draw(QPainter *painter);

private:
    QString pic;
    QPoint pos;
signals:

public slots:
};

#endif // CARROT_H
