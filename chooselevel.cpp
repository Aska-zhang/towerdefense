#include "chooselevel.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QDebug>
#include<QLabel>

chooselevel::chooselevel(QWidget *parent) : QMainWindow(parent)
{
    //设置标题
    this->setWindowTitle("我的萝卜我做主");
    //设置图标
    this->setWindowIcon(QIcon(":/res/carrot/pic15.png"));

    //设置固定大小
    setFixedSize(1200,800);

    //返回按钮
    mypushbutton * backBtn = new mypushbutton(":/res/mainscene/BackButton.png" , ":/res/mainscene/BackButtonSelected.png");
    backBtn->setParent(this);
    connect(backBtn,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            emit this->choosesceneback();
        });
    });

    QString pic[12]={":/res/gameover0/pic2.png",":/res/gameover0/pic3.png",":/res/gameover0/pic4.png",":/res/gameover0/pic5.png",
                    ":/res/gameover0/pic6.png",":/res/gameover0/pic7.png",":/res/gameover0/pic8.png",":/res/gameover0/pic9.png",
                    ":/res/gameover0/pic10.png",":/res/gameover0/pic1.png"};

    QString background[12]={":/res/gamescene/scene1/BG1-hd.png",":/res/gamescene/scene1/BG1-hd.png",":/res/gamescene/scene1/BG1-hd.png",":/res/gamescene/scene1/BG2-hd.png",
                        ":/res/gamescene/scene2/BG1-hd.png",":/res/gamescene/scene2/BG1-hd.png",":/res/gamescene/scene2/BG2-hd.png",":/res/gamescene/scene2/BG1-hd.png",
                        ":/res/gamescene/scene3/BG1-hd.png",":/res/gamescene/scene3/BG1-hd.png",":/res/gamescene/scene3/BG2-hd.png",":/res/gamescene/scene3/BG2-hd.png",};
    QString playway[12]={":/res/gamescene/scene1/1.png",":/res/gamescene/scene1/2.png",":/res/gamescene/scene1/3-2.png",":/res/gamescene/scene1/4-2.png",
                        ":/res/gamescene/scene2/1.png",":/res/gamescene/scene2/2.png",":/res/gamescene/scene2/3.png",":/res/gamescene/scene2/4.png",
                        ":/res/gamescene/scene3/1.png",":/res/gamescene/scene3/2.png",":/res/gamescene/scene3/3.png",":/res/gamescene/scene3/4.png",};

    //萝卜位置
    QPoint carrot[12]={QPoint(this->width()*0.85,this->height()*0.11),QPoint(this->width()*0.58,this->height()*0.65),QPoint(this->width()*0.88,this->height()*0.12)
                      ,QPoint(this->width()*0.85,this->height()*0.12),QPoint(this->width()*0.73,this->height()*0.68),QPoint(this->width()*0.37,this->height()*0.14)
                      ,QPoint(this->width()*0.84,this->height()*0.17),QPoint(this->width()*0.856,this->height()*0.68),QPoint(this->width()*0.851,this->height()*0.2)
                      ,QPoint(this->width()*0.77,this->height()*0.19),QPoint(this->width()*0.91,this->height()*0.69),QPoint(this->width()*0.91,this->height()*0.69)};

    int turn[12]={8,6,2,10,6,9,7,9,9,8,4,9};
    QPoint Q[12][10]={{QPoint(150,237.5),QPoint(150, 537.5),QPoint(462.5, 537.5)
                     ,QPoint(462.5, 425),QPoint(762.5, 425),QPoint(762.5, 537.5)
                     ,QPoint(1058.5, 537.5),QPoint(1058.5, 237.5),QPoint(0,0),QPoint(0,0)},
                    {QPoint(462.5, 237.5),QPoint(950, 237.5),QPoint(950, 440),
                    QPoint(250, 440),QPoint(250, 650),QPoint(737.5, 650),
                    QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0)},
                    {QPoint(75, 225),QPoint(1122.5, 225),QPoint(0,0),QPoint(0,0),
                    QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),
                    QPoint(0,0),QPoint(0,0)},
                    {QPoint(250, 237.5),QPoint(250, 543.75),QPoint(550, 543.75),QPoint(550, 237.5),
                    QPoint(856.25, 237.5),QPoint(856.25,431.25),QPoint(762.5, 431.25),QPoint(762.5, 643.75),
                    QPoint(1055, 643.75),QPoint(1055, 237.5)},
                    {QPoint(50, 237.5),QPoint(956.25, 237.5),QPoint(956.25, 450),
                    QPoint(250, 450),QPoint(250, 662.5),QPoint(950,662.5),QPoint(0,0),
                    QPoint(0,0),QPoint(0,0),QPoint(0,0)},
                    {QPoint(143.75, 237.5),QPoint(143.75, 656.25),QPoint(462.5, 656.25),
                    QPoint(462.5, 460),QPoint(856.25, 460),QPoint(856.25,656.25),
                    QPoint(1062.5, 656.25),QPoint(1062.5, 237.5),QPoint(473, 237.5),QPoint(0,0)},
                    {QPoint(250, 656.25),QPoint(250, 262.5),QPoint(550, 262.5),
                    QPoint(550, 656.25),QPoint(856.25, 656.25),QPoint(856.25,262.5),
                    QPoint(1031.25, 262.5),QPoint(0,0),QPoint(0,0),QPoint(0,0)},
                    {QPoint(275, 475),QPoint(650, 475),QPoint(650, 262.5),QPoint(756.25, 262.5),
                    QPoint(756.25, 681.25),QPoint(950,681.25),QPoint(950, 262.5),
                    QPoint(1062.5, 262.5),QPoint(1062.5, 650),QPoint(0,0)},
                    {QPoint(87.5, 362.5),QPoint(250, 362.5),QPoint(250, 681.35),
                    QPoint(456.25, 681.25),QPoint(456.25, 470),QPoint(756.25,470),
                    QPoint(756.25, 681.25),QPoint(1058, 681.25),QPoint(1058, 275),QPoint(0,0)},
                    {QPoint(287.5, 681.25),QPoint(962.5, 681.25),QPoint(962.5, 575),
                    QPoint(456.25, 575),QPoint(456.25, 362.5),QPoint(250,362.5),
                    QPoint(250, 265),QPoint(962.5, 265),QPoint(0,0),QPoint(0,0)},
                    {QPoint(137.5, 260),QPoint(550, 260),QPoint(550, 681.25),QPoint(550, 681.25),
                    QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0)},
                    {QPoint(150, 625),QPoint(150, 260),QPoint(456.25, 260),QPoint(456.25, 468.75),
                    QPoint(756.25, 468.75),QPoint(756.25,260),QPoint(962.5, 260),QPoint(958, 681.25),
                    QPoint(1083, 681.25),QPoint(0,0)}};
    QPoint **q=new QPoint* [12];
    int i=0,j=0;
    for(i=0;i<12;i++)
    {
        q[i]=new QPoint[turn[i]];
    }
    for(i=0;i<12;i++)
    {
        for(j=0;j<turn[i];j++)
        {
            q[i][j]=Q[i][j];
        }
    }

    //创建选择关卡的按钮
    for( int i = 0 ; i < 12 ;i ++)
    {
        mypushbutton * menuBtn = new mypushbutton(":/res/mainscene/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move( 580 + i%3 * 150 , 200 + i/3 * 145  );

       // 监听每个按钮的点击事件
        connect(menuBtn,&mypushbutton::clicked,[=](){
            QString str = QString("您选择的是第 %1 关 ").arg( i + 1);
            qDebug() <<str;

            //进入到游戏场景
            this->hide(); //将选关场景隐藏掉
            play = new playscene(i+1,turn[i],q[i],background[i],playway[i]); //创建游戏场景
            play->show();//显示游戏场景

            connect(play,&playscene::choosesceneback,[=](){
                this->show();
                delete play;
                play = NULL;
            });

        });

//          QPixmap * pix = new QPixmap;
//          //pix->setParent(this);
//          if(i<9)
//          {
//              pix->load(pic[i]);
//              pix=pix->scaled(pix.width()*2,pix.height()*2);
//          }
//          else {
//              pix->load(pic[0]);
//              QPixmap * pix2 = new QPixmap;
//          }


        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(580 + i%3 * 150 , 200 + i/3 * 145 );

        //设置 label上的文字对齐方式 水平居中和 垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void chooselevel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/mainscene/pic0.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
