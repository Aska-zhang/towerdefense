#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QDebug>
#include"mypushbutton.h"
#include<QTimer>
#include<QMediaPlayer>


MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置标题
    this->setWindowTitle("我的萝卜我做主");
    //设置图标
    this->setWindowIcon(QIcon(":/res/carrot/pic15.png"));

    //设置固定大小
    setFixedSize(1200,800);

    //设置开始按钮
    mypushbutton *startbtn=new mypushbutton(":/res/mainscene/pic19.png",":/res/mainscene/pic15.png");
    startbtn->setParent(this);
    startbtn->move(this->width() / 3 - startbtn->width()-30  ,this->height() * 0.83 );

    mypushbutton *startbtn2=new mypushbutton(":/res/mainscene/pic6.png",":/res/mainscene/pic2.png");
    startbtn2->setParent(this);
    startbtn2->move(this->width()*2 / 3 - startbtn2->width()-25  ,this->height() * 0.83 );

    mypushbutton *startbtn3=new mypushbutton(":/res/mainscene/pic8.png",":/res/mainscene/pic7.png");
    startbtn3->setParent(this);
    startbtn3->move(this->width()  - startbtn3->width()-30 ,this->height() * 0.83 );

    audioPlayer = new AudioPlayer(1,this);
    audioPlayer->startBGM();

//    QMediaPlayer* player = new QMediaPlayer;
//    player->setMedia(QUrl("qrc:/music/BGMusic.mp3"));//指定源为qrc文件
//    player->setVolume(50);
//    player->play();



    //点击后进入选关
    choosescene=new chooselevel;
    connect(startbtn, &QPushButton::clicked,[=](){
        startbtn->zoom1();
        startbtn->zoom2();

        //延时进入到选择关卡场景中,延时0.5秒后进入
        QTimer::singleShot(500,this,[=](){
            audioPlayer->stopBGM();
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            choosescene->show();
        });
    });
    //两个没什么用的按钮，放这吧
    connect(startbtn2, &QPushButton::clicked,[=](){
        startbtn2->zoom1();
        startbtn2->zoom2();});
    connect(startbtn3, &QPushButton::clicked,[=](){
        startbtn3->zoom1();
        startbtn3->zoom2();});


    connect(choosescene,&chooselevel::choosesceneback,this,[=](){

        choosescene->hide(); //将选择关卡场景 隐藏掉
        this->show(); //重新显示主场景
        audioPlayer->startBGM();
    });


}

MainScene::~MainScene()
{
    delete ui;
}


void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/mainscene/pic1.png");
    painter .drawPixmap(0,0,this->width(),this->height(),pix);


    //画萝卜叶子们
    pix.load(":/res/mainscene/pic26.png");
    //qDebug()<<pix.width()<<" "<<pix.height();
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(418,180,pix);

    pix.load(":/res/mainscene/pic34.png");
    //qDebug()<<pix.width()<<" "<<pix.height();
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(635,170,pix);

    pix.load(":/res/mainscene/pic22.png");
    //qDebug()<<pix.width()<<" "<<pix.height();
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(510,130,pix);


    //画萝卜
    pix.load(":/res/mainscene/pic13.png");
    //qDebug()<<pix.width()<<" "<<pix.height();
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(460,280,pix);


    //画标题
    pix.load(":/res/mainscene/pic3.png");
    //pix.scale
   // qDebug()<<pix.width();
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(315,280,pix);

    //画飞在天上的黄色小东西
    pix.load(":/res/mainscene/pic9.png");
    //qDebug()<<pix.width()<<" "<<pix.height();
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(80,200,pix);




}
