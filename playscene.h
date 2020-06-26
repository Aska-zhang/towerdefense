#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QList>
#include"tower.h"
#include"mypushbutton2.h"
#include"bullet.h"
#include"moveway.h"
#include"monster.h"
#include"bullet.h"
class monster;
class playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playscene(QWidget *parent = nullptr);

    playscene(int levelNum, int turns,QPoint carrotp,QPoint en,QPoint *Qturn, QString picpath,QString waypath,QWidget *parent = nullptr);

    int levelIndex ; //内部成员属性 记录所选的关卡
    int num_of_turn;

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);
    QString picturepath;
    QString wpath;
    QPoint carrotpos;
    void mousePressEvent(QMouseEvent *e);
    QPoint pos[12][8];
    void drawkk(QPainter *painter);

    void addwaypoints();
    void getHpDamage(int damage = 1);
    void removedEnemy(monster *monster);
    void removedBullet(bullet *bullets);
    void addBullet(bullet *bullets);
    void awardGold(int gold);
    void minusgold(int gold);
    QList<monster *> enemyList() const;

    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();

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
    QPoint *turn;//拐弯点
    QPoint carrot;
    QPoint entry;


    QList<moveway *> waypointslist;
    QList<monster *> enemylist;
    QList<bullet *> bulletlist;
    QList<QVariant> wavesInfo;


    bool loadWave();


//    mypushbutton2 *stb1;
//    mypushbutton2 *stb2;
//    mypushbutton2 *stb3;




signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void choosesceneback();

public slots:
    void updateMap();
    void gameStart();
};

#endif // PLAYSCENE_H
