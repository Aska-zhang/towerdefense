#include "playscene.h"
#include<QPainter>
#include<QDebug>
#include"mypushbutton.h"
#include"mypushbutton2.h"
#include<QTimer>
#include<QMouseEvent>
#include<math.h>
#include"tower.h"
#include"bullet.h"
//playscene::playscene(QWidget *parent) : QMainWindow(parent)
//{

//}
QPoint Q1[8]={QPoint(150,237.5),QPoint(150, 537.5),QPoint(462.5, 537.5)
             ,QPoint(462.5, 425),QPoint(762.5, 425),QPoint(762.5, 537.5)
             ,QPoint(1058.5, 537.5),QPoint(1058.5, 237.5)};
playscene::playscene(int levelNum,int turns,QPoint *Qturn, QString picpath,QString waypath,QWidget *parent):picturepath(picpath),wpath(waypath), QMainWindow(parent)
{
    num_of_turn=turns;
    turn=Qturn;

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
        qDebug() << "翻金币场景中：点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
            emit this->choosesceneback();
        });

    });

    addwaypoints();
//    connect(stb1,&QPushButton::click,[=](){
//       tower *t=new tower(realpos);
//       towersList.push_back(t);
//       qDebug()<<"jianta";
//       stb1->hide();stb2->hide();stb3->hide();
//       delete stb1;delete  stb2;delete stb3;
//    });

}

void playscene::addwaypoints()//添加地图上的拐点,根据关卡找turn指针的第i个，从而获得具体的转折点的位置
{
//    moveway *wayPoint1 = new moveway(QPoint(150, 625));
//    waypointslist.push_back(wayPoint1);

//    moveway *wayPoint2 = new moveway(QPoint(150, 260));
//    waypointslist.push_back(wayPoint2);
//    wayPoint2->setNextWayPoint(wayPoint1);

//    moveway *wayPoint3 = new moveway(QPoint(456.25, 260));
//    waypointslist.push_back(wayPoint3);
//    wayPoint3->setNextWayPoint(wayPoint2);

//    moveway *wayPoint4 = new moveway(QPoint(456.25, 468.75));
//    waypointslist.push_back(wayPoint4);
//    wayPoint4->setNextWayPoint(wayPoint3);

//    moveway *wayPoint5 = new moveway(QPoint(756.25, 468.75));
//    waypointslist.push_back(wayPoint5);
//    wayPoint5->setNextWayPoint(wayPoint4);

//    moveway *wayPoint6 = new moveway(QPoint(756.25,260));
//    waypointslist.push_back(wayPoint6);
//    wayPoint6->setNextWayPoint(wayPoint5);

//    moveway *wayPoint7 = new moveway(QPoint(962.5, 260));
//    waypointslist.push_back(wayPoint7);
//    wayPoint7->setNextWayPoint(wayPoint6);

//    moveway *wayPoint8 = new moveway(QPoint(958, 681.25));
//    waypointslist.push_back(wayPoint8);
//    wayPoint8->setNextWayPoint(wayPoint7);

//    moveway *wayPoint9 = new moveway(QPoint(1083, 681.25));
//    waypointslist.push_back(wayPoint9);
//    wayPoint9->setNextWayPoint(wayPoint8);

//    moveway *wayPoint10 = new moveway(QPoint(445, 237.5));
//    waypointslist.push_back(wayPoint10);
//    wayPoint10->setNextWayPoint(wayPoint9);

    moveway **wayPoint=new moveway*[num_of_turn];//=new moveway[num_of_turn];
    for(int i=0;i<num_of_turn;i++)
    {
        wayPoint[i]=new moveway(turn[i]);
        waypointslist.push_back(wayPoint[i]);
        if(i>0)
        {
            wayPoint[i]->setNextWayPoint(wayPoint[i-1]);
        }
    }
}

void playscene::paintEvent(QPaintEvent *)
{
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
    //画萝卜
    pix.load(":/res/carrot/pic15.png");
    pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);
    painter .drawPixmap(this->width()*0.77,this->height()*0.19,pix);

    if(ifdrawkk==true)
    {
        drawkk(&painter);
    }

    foreach (const tower *t, towersList)
        t->draw(&painter);
    foreach (const moveway *wayPoint, waypointslist)
        wayPoint->draw(&painter);


}
void playscene::mousePressEvent(QMouseEvent *e)
{

    QPoint pressPos=e->pos();
    QPoint realpos=QPoint(floor(pressPos.x()/100)*100,floor(pressPos.y()/100)*100);
    if(e->button()==Qt::LeftButton)
    {
        int x1=floor(pressPos.x()/100);int y1=floor(pressPos.y()/100);
        if(canputtower[x1][y1])
        {

        ifdrawkk=true;//框框，就是选择放哪个炮塔时候的那个
        drawkkpos=realpos;
        mypushbutton2 *stb1=new mypushbutton2(":/res/TBottle/pic12.png",":/res/TBottle/pic13.png");
        stb1->setParent(this);
        stb1->move(drawkkpos.x()-100,drawkkpos.y()+100);
        stb1->show();
        mypushbutton2 *stb2 = new mypushbutton2(":/res/TPlane/pic10.png" , ":/res/TPlane/pic11.png");
        stb2->setParent(this);
        stb2->move(drawkkpos.x(),drawkkpos.y()+100);
        stb2->show();
       mypushbutton2 * stb3=new mypushbutton2(":/res/TBlueStar/pic50.png",":/res/TBlueStar/pic17.png");
        stb3->setParent(this);
        stb3->move(drawkkpos.x()+100,drawkkpos.y()+100);
        stb3->show();
        mypushbutton2 * stbcancel=new mypushbutton2(":/res/TBlueStar/pic50.png",":/res/TBlueStar/pic17.png");
         stbcancel->setParent(this);
         stbcancel->move(drawkkpos.x()+200,drawkkpos.y()+100);
         stbcancel->show();
        update();
        connect(stb1,&QPushButton::clicked,[=](){
           tower *t=new tower(realpos,this);
           towersList.push_back(t);
           //qDebug()<<"jianta";
           //stb1->hide();stb2->hide();stb3->hide();
           delete stb1;delete  stb2;delete stb3;delete stbcancel;
           ifdrawkk=false;
           canputtower[x1][y1]=false;
           update();
        });
        connect(stb2,&QPushButton::clicked,[=](){
           tower *t=new tower(realpos,this);
           towersList.push_back(t);
           //qDebug()<<"jianta";
           //stb1->hide();stb2->hide();stb3->hide();
           delete stb1;delete  stb2;delete stb3;delete stbcancel;
           ifdrawkk=false;
           canputtower[x1][y1]=false;
           update();
        });
        connect(stb3,&QPushButton::clicked,[=](){
           tower *t=new tower(realpos,this);
           towersList.push_back(t);
           //qDebug()<<"jianta";
           //stb1->hide();stb2->hide();stb3->hide();
           delete stb1;delete  stb2;delete stb3;delete stbcancel;
           ifdrawkk=false;
           canputtower[x1][y1]=false;
           update();
        });
        connect(stbcancel,&QPushButton::clicked,[=](){
            delete stb1;delete  stb2;delete stb3;delete stbcancel;
            ifdrawkk=false;
            update();
        });
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
