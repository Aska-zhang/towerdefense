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
            play = new playscene(i+1,background[i],playway[i]); //创建游戏场景
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
