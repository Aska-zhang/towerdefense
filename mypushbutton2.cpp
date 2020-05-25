#include "mypushbutton2.h"
#include<QDebug>

//mypushbutton2::mypushbutton2(QWidget *parent) : QWidget(parent)
//{

//}
mypushbutton2::mypushbutton2(QString moneyImg, QString noImg  )
{
    this->moneyImgPath = moneyImg;
    this->noImgPath = noImg;

    QPixmap pix;
    bool ret = pix.load(moneyImg);
    if(!ret)
    {
       qDebug() << "图片加载失败";
       return;
    }

    pix=pix.scaled(100,100);

    //设置图片固定大小
    this->setFixedSize( 100,100);

    //设置不规则图片样式,去边框
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
    qDebug()<<"chenggong";
}
