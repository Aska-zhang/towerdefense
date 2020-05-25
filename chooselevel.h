#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include"playscene.h"

class chooselevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevel(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    playscene * play = NULL;

signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void choosesceneback();

public slots:
};

#endif // CHOOSELEVEL_H
