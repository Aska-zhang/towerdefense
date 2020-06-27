#include "playscene.h"
#include<QPainter>
#include<QDebug>
#include"mypushbutton.h"
#include"mypushbutton2.h"
#include<QTimer>
#include<QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include<math.h>
#include<QtMath>
#include<cmath>
#include"tower.h"
#include"bullet.h"
#include"monster.h"
#include"audioplayer.h"
#include <QMediaPlayer>
//playscene::playscene(QWidget *parent) : QMainWindow(parent)
//{

//}
static const int TowerCost = 100;
playscene::playscene(int levelNum,int turns,QPoint carrotp,QPoint en,QPoint *Qturn, QString picpath,QString waypath,QWidget *parent):picturepath(picpath),wpath(waypath), QMainWindow(parent)
{
    num_of_turn=turns;
    turn=Qturn;
    carrot=carrotp;
    entry=en;
    Hp=10;
    playrGold=1000;gameEnded=false;gameWin=false;
    wave=0;

    this->setAttribute(Qt::WA_DeleteOnClose,1);

    this->levelIndex = levelNum;
    ifdrawkk=false;
    //设置标题
    this->setWindowTitle("我的萝卜我做主");
    //设置图标
    this->setWindowIcon(QIcon(":/res/carrot/pic15.png"));

    //设置固定大小
    setFixedSize(1200,800);

    int i,j;
    for(i=0;i<=11;i++)
    {
        for(j=0;j<=7;j++)
        {
            int x=i*100;int y=j*100;
            pos[i][j]=QPoint(x,y);
            canputtower[i][j]=true;
        }
    }

    mypushbutton * backBtn = new mypushbutton(":/res/mainscene/BackButton.png" , ":/res/mainscene/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&mypushbutton::clicked,[=](){
//        qDebug() << "翻金币场景中：点击了返回按钮";
//        foreach ( tower *t, towersList)
//            delete t;
//        foreach ( moveway *wayPoint, waypointslist)
//            delete wayPoint;
//        foreach ( monster *enemy, enemylist)
//            delete enemy;
//        foreach ( bullet *bullets, bulletlist)
//            delete bullets;

        QTimer::singleShot(500,this,[=](){
            this->close();
            emit this->choosesceneback();
//            this->close();
        });

    });

    addwaypoints();

    audioPlayer = new AudioPlayer(2,this);
    audioPlayer->startBGM();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(20);
//300ms后开始游戏
    qDebug()<<"*1";
    QTimer::singleShot(300, this, SLOT(gameStart()));


}

void playscene::addwaypoints()//添加地图上的拐点,根据关卡找turn指针的第i个，从而获得具体的转折点的位置
{
//    moveway *wayPoint1 = new moveway(QPoint(150, 625));
//    waypointslist.push_back(wayPoint1);

//    moveway *wayPoint2 = new moveway(QPoint(150, 260));
//    waypointslist.push_back(wayPoint2);
//    wayPoint2->setNextWayPoint(wayPoint1);

    moveway **wayPoint=new moveway*[num_of_turn];//=new moveway[num_of_turn];
    for(int i=num_of_turn-1;i>=0;i--)
    {
        wayPoint[i]=new moveway(turn[i]);
        waypointslist.push_back(wayPoint[i]);
        if(i<num_of_turn-1)
        {
            wayPoint[i]->setNextWayPoint(wayPoint[i+1]);
        }
    }
}

void playscene::getHpDamage(int damage)
{
    audioPlayer->playSound(BigBoss);
    Hp -= damage;
    if (Hp <= 0)
        doGameOver();
}

void playscene::removedEnemy(monster *enemy)
{
    Q_ASSERT(enemy);

    enemylist.removeOne(enemy);
    delete enemy;

    if (enemylist.empty())
    {
        ++wave;
        if (!loadWave())
        {
            gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
void playscene::removedBullet(bullet *bullets)
{
    Q_ASSERT(bullets);

    bulletlist.removeOne(bullets);
    delete bullets;
}

void  playscene::updateMap()
{
    if(Hp<=0)
        doGameOver();
//        gameEnded=true;
    foreach (monster *enemy, enemylist)
        enemy->move();
    foreach (tower *t, towersList)
        t->checkEnemyInRange();
//    foreach (bullet *b, bulletlist)
//        b->move();
    update();
}

void playscene::addBullet(bullet *bullets)
{
    Q_ASSERT(bullets);

    bulletlist.push_back(bullets);
}

bool playscene::canBuyTower(tower* t) const
{
    if(t->gettag()==1)
    {
        if (playrGold >= dynamic_cast<Bottle*>(t)->cost)
            return true;
    }
    if(t->gettag()==2)
    {
        if (playrGold >= dynamic_cast<Pin*>(t)->cost)
            return true;
    }
    if(t->gettag()==3)
    {
        if (playrGold >= dynamic_cast<star*>(t)->cost)
            return true;
    }
//    if (playrGold >= dynamic_cast<Bottle*>(t)->cost)
//        return true;
    return false;
}

void playscene::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(wave + 1));
}

void playscene::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(Hp));
}

void playscene::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(playrGold));
}

void playscene::doGameOver()
{
    if (!gameEnded)
    {
        gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void playscene::awardGold(int gold)
{
    playrGold += gold;
    update();
}
void playscene::minusgold(int gold)
{
    playrGold -= gold;
    update();
}

bool playscene::loadWave()
{
//	if (wave >= wavesInfo.size())
//		return false;

//	moveway *startWayPoint = waypointslist.back();
//	QList<QVariant> curWavesInfo = wavesInfo[wave].toList();

//	for (int i = 0; i < curWavesInfo.size(); ++i)
//	{
//		QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
//		int spawnTime = dict.value("spawnTime").toInt();

    QString q[12]={":/res/Monsters1/pic1.png",":/res/Monsters1/pic2.png",":/res/Monsters1/pic3.png",":/res/Monsters1/pic4.png",
                  ":/res/Monsters2/pic5.png",":/res/Monsters2/pic4.png",":/res/Monsters2/pic23.png",":/res/Monsters2/pic3.png",
                  ":/res/Monsters3/pic15.png",":/res/Monsters3/pic2.png",":/res/Monsters3/pic3.png",":/res/Monsters3/pic12.png"};
//		monster *enemy = new monster(startWayPoint, this,q);
//		enemylist.push_back(enemy);
//		QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
//	}

//	return true;
//    qDebug()<<wave;
    if (wave >= 21)
            {
        gameWin=true;
        return false;
    }
       moveway *startWayPoint = waypointslist.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 100, 2100, 4100, 6100, 8100, 10100,12100,14100,16100,18100 };
        int hp1,hp2;
        if(wave<=15)//随着波数增加，怪物的血量上升
        {
            hp1=150*floor(wave/5+1);
            hp2=220*floor(wave/5+1);
        }
        int i1,i2,i3,i4;
        if(levelIndex<=4)
        {
            i1=0;i2=1;i3=2;i4=3;
        }
        if(levelIndex>=5&&levelIndex<=8)
        {
            i1=4;i2=5;i3=6;i4=7;
        }
        if(levelIndex>=9&&levelIndex<=12)
        {
            i1=8;i2=9;i3=10;i4=11;
        }

        for (int i = 0; i < 10; ++i)
        {
            if(wave%4==1)
            {
                monster *enemy = new monster(startWayPoint,1,hp1 ,this,q[i2]);
                enemylist.push_back(enemy);
                QTimer::singleShot(enemyStartInterval[i],enemy, SLOT(becomealive()));
            }
            if(wave%4==2)
            {
                monster1 *enemy = new monster1(startWayPoint,2,hp2, this,q[i3]);
                enemylist.push_back(enemy);
                QTimer::singleShot(enemyStartInterval[i],enemy, SLOT(becomealive()));
            }
            if(wave%4==3)
            {
                monster2 *enemy = new monster2(startWayPoint,3,hp2 ,this,q[i4]);
                enemylist.push_back(enemy);
                QTimer::singleShot(enemyStartInterval[i],enemy, SLOT(becomealive()));
            }
            if(wave%4==0)
            {
                monster3 *enemy = new monster3(startWayPoint,4,hp1 ,this,q[i1]);
                enemylist.push_back(enemy);
                QTimer::singleShot(enemyStartInterval[i],enemy, SLOT(becomealive()));
            }
//            monster *enemy = new monster(startWayPoint,1, this,q);
//            enemylist.push_back(enemy);
//            QTimer::singleShot(enemyStartInterval[i],enemy, SLOT(becomealive()));
        }
        return true;
}

void playscene::paintEvent(QPaintEvent *)
{
    if (gameEnded || gameWin)
    {
        QString text = gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
//        return;
    }
    if (gameEnded)
    {
        QPainter painter1(this);
        QPixmap pix1;
        pix1.load(":/res/gameover0/pic23.png");
        painter1 .drawPixmap(0,0,this->width(),this->height(),pix1);
        return;
    }

    if (gameWin)
    {
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/res/gameover0/pic34.png");
        painter .drawPixmap(0,0,this->width(),this->height(),pix);
    }

    QPainter painter(this);
    QPixmap pix;
    pix.load(picturepath);
    //pix.load(":/res/gamescene/scene1/BG1-hd.png");
    //qDebug() <<picturepath;
    painter .drawPixmap(0,0,this->width()*1.1,this->height()*1.59,pix);

    //画路
    pix.load(wpath);
    pix=pix.scaled(pix.width()*1.25,pix.height()*1.3);
    painter .drawPixmap(0,170,pix);
    //画出怪地
    pix.load(":/res/Object1-1/pic8.png");
    pix=pix.scaled(100,100);
    painter .drawPixmap(entry.x()-50,entry.y()-50,pix.width(),pix.height(),pix);


    //画萝卜
    if(Hp==10)
    {
        pix.load(":/res/carrot/pic15.png");
        pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);
        painter .drawPixmap(carrot,pix);
    }
    else if(Hp<10&&Hp>7)
    {
        pix.load(":/res/carrot/pic10.png");
        pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);
        painter .drawPixmap(carrot,pix);
    }
    else if(Hp<=7&&Hp>=4)
    {
        pix.load(":/res/carrot/pic12.png");
        pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);
        painter .drawPixmap(carrot,pix);
    }
    else
    {
        pix.load(":/res/carrot/pic23.png");
        pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);
        painter .drawPixmap(carrot,pix);
    }

    if(ifdrawkk==true)
    {
        drawkk(&painter);
    }

    foreach (const tower *t, towersList)
        t->draw(&painter);
    foreach (const moveway *wayPoint, waypointslist)
        wayPoint->draw(&painter);
    foreach (const monster *enemy, enemylist)
        enemy->draw(&painter);
    foreach (const bullet *bullets, bulletlist)
        bullets->draw(&painter);
    drawWave(&painter);
    drawHP(&painter);
    drawPlayerGold(&painter);

}
void playscene::mousePressEvent(QMouseEvent *e)
{

    QPoint pressPos=e->pos();
    QPoint realpos=QPoint(floor(pressPos.x()/100)*100,floor(pressPos.y()/100)*100);
    int x1=floor(pressPos.x()/100);int y1=floor(pressPos.y()/100);
    if(e->button()==Qt::LeftButton)
    {

        if(canputtower[x1][y1])
        {

        ifdrawkk=true;//框框，就是选择放哪个炮塔时候的那个
        drawkkpos=realpos;
        audioPlayer->playSound(Towerselect);

        mypushbutton2 *stb1=new mypushbutton2(":/res/TBottle/pic12.png",":/res/TBottle/pic13.png");
        stb1->setParent(this);
        stb1->move(drawkkpos.x()-100,drawkkpos.y()+100);
        stb1->show();
        mypushbutton2 *stb2 = new mypushbutton2(":/res/TPin/pic1.png" , ":/res/TPin/pic2.png");
        stb2->setParent(this);
        stb2->move(drawkkpos.x(),drawkkpos.y()+100);
        stb2->show();
       mypushbutton2 * stb3=new mypushbutton2(":/res/TBlueStar/pic50.png",":/res/TBlueStar/pic17.png");
        stb3->setParent(this);
        stb3->move(drawkkpos.x()+100,drawkkpos.y()+100);
        stb3->show();
        mypushbutton2 * stbcancel=new mypushbutton2(":/res/mainscene/LevelIcon.png",":/res/TBlueStar/pic17.png");
         stbcancel->setParent(this);
         stbcancel->move(drawkkpos.x()+200,drawkkpos.y()+100);
         stbcancel->show();
        update();
        connect(stb1,&QPushButton::clicked,[=](){

           Bottle *t=new Bottle(realpos,1,this);
           if(canBuyTower(t))
           {
           towersList.push_back(t);
            minusgold(t->cost);
           canputtower[x1][y1]=false;
           audioPlayer->playSound(TowerBuild);}
           else {
               delete t;canputtower[x1][y1]=true;
           }
           //qDebug()<<"jianta";
           //stb1->hide();stb2->hide();stb3->hide();
           delete stb1;delete  stb2;delete stb3;delete stbcancel;
           ifdrawkk=false;
//           canputtower[x1][y1]=false;
           update();
        });
        connect(stb2,&QPushButton::clicked,[=](){

           Pin *t=new Pin(realpos,2,this);
           if(canBuyTower(t))
           {
           towersList.push_back(t);
            minusgold(t->cost);
           canputtower[x1][y1]=false;
           audioPlayer->playSound(TowerBuild);}
           else {
               delete t;
               canputtower[x1][y1]=true;
           }
           //qDebug()<<"jianta";
           //stb1->hide();stb2->hide();stb3->hide();
           delete stb1;delete  stb2;delete stb3;delete stbcancel;
           ifdrawkk=false;
//           canputtower[x1][y1]=false;
           update();
        });
        connect(stb3,&QPushButton::clicked,[=](){

           star *t=new star(realpos,3,this);
           if(canBuyTower(t))
           {
           towersList.push_back(t);
            minusgold(t->cost);
           canputtower[x1][y1]=false;
           audioPlayer->playSound(TowerBuild);}
           else {
               delete t;
               canputtower[x1][y1]=true;
           }
           //qDebug()<<"jianta";
           //stb1->hide();stb2->hide();stb3->hide();
           delete stb1;delete  stb2;delete stb3;delete stbcancel;
           ifdrawkk=false;

           update();
        });
        connect(stbcancel,&QPushButton::clicked,[=](){
            delete stb1;delete  stb2;delete stb3;delete stbcancel;
            ifdrawkk=false;canputtower[x1][y1]=true;
            update();
        });
        }
        else {
            foreach (tower *t, towersList)
                if(t->position()==realpos)
                {
                    if(t->gettag()==1)
                    {
//                        t=dynamic_cast<Bottle *>(t);
                        if(dynamic_cast<Bottle *>(t)->upgrade==false&&dynamic_cast<Bottle *>(t)->upcost<playrGold)
                        {dynamic_cast<Bottle *>(t)->up();
                        playrGold-=dynamic_cast<Bottle *>(t)->upcost;
                        audioPlayer->playSound(Towerupdata);}
                    }
                    if(t->gettag()==2)
                    {
//                        t=dynamic_cast<Pin *>(t);
                        if(dynamic_cast<Pin *>(t)->upgrade==false&&dynamic_cast<Pin *>(t)->upcost<playrGold)
                        {dynamic_cast<Pin *>(t)->up();
                        playrGold-=dynamic_cast<Pin *>(t)->upcost;
                        audioPlayer->playSound(Towerupdata);}
                    }
                    if(t->gettag()==3)
                    {
//                        t=dynamic_cast<Pin *>(t);
                        if(dynamic_cast<star *>(t)->upgrade==false&&dynamic_cast<star *>(t)->upcost<playrGold)
                        {dynamic_cast<star *>(t)->up();
                        playrGold-=dynamic_cast<star *>(t)->upcost;
                        audioPlayer->playSound(Towerupdata);}
                    }

                }
        }



    }
    if(e->button()==Qt::RightButton)
    {
//        qDebug()<<"right";
        foreach (tower *t, towersList)
        {
            if(t->position().x()==realpos.x()&&t->position().y()==realpos.y())
            {
//                qDebug()<<"delete";
                Q_ASSERT(t);
                towersList.removeOne(t);
                delete t;
                canputtower[x1][y1]=true;
                playrGold+=TowerCost*0.8;
                audioPlayer->playSound(TowerSell);
            }
        }
    }
}
void playscene::drawkk(QPainter *painter)
{
    QPixmap p;
    p.load(":/res/boardnode.png");
    painter->drawPixmap(drawkkpos.x(),drawkkpos.y(),100,100,p);
//    p.load(":/res/TBottle/pic12");
//    painter->drawPixmap(drawkkpos.x()-100,drawkkpos.y()+100,100,100,p);
//    p.load(":/res/TPlane/pic10");
//    painter->drawPixmap(drawkkpos.x(),drawkkpos.y()+100,100,100,p);
//    p.load(":/res/TBlueStar/pic50");
//    painter->drawPixmap(drawkkpos.x()+100,drawkkpos.y()+100,100,100,p);
//    mypushbutton2 *stb1=new mypushbutton2(":/res/TBottle/pic12");
//    stb1->setParent(this);
//    stb1->move(drawkkpos.x()-100,drawkkpos.y()+100);
//    mypushbutton2 *stb2=new mypushbutton2(":/res/TPlane/pic10");
//    stb2->move(drawkkpos.x(),drawkkpos.y()+100);
//    mypushbutton2 *stb3=new mypushbutton2(":/res/TBlueStar/pic50");
//    stb3->move(drawkkpos.x()+100,drawkkpos.y()+100);
}

void playscene::gameStart()
{
    qDebug()<<"start";
    loadWave();
}
QList<monster *> playscene::enemyList() const
{
    return enemylist;
}
