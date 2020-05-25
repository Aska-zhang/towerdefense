#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QList>
#include"tower.h"
#include"mypushbutton2.h"
#include"bullet.h"

class playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playscene(QWidget *parent = nullptr);

    playscene(int levelNum, QString picpath,QString waypath,QWidget *parent = nullptr);

    int levelIndex ; //内部成员属性 记录所选的关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);
    QString picturepath;
    QString wpath;
    QPoint carrotpos;
    void mousePressEvent(QMouseEvent *e);
    QPoint pos[12][8];
    void drawkk(QPainter *painter);

private:
    int	wave;
    int	Hp;
    int	playrGold;
    bool gameEnded;
    bool gameWin;
    QList<tower *> towersList;
    bool ifdrawkk;
    bool canputtower[12][8];
    QPoint drawkkpos;//画加炮塔的框的坐标

//    mypushbutton2 *stb1;
//    mypushbutton2 *stb2;
//    mypushbutton2 *stb3;




signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void choosesceneback();

public slots:
};

#endif // PLAYSCENE_H
