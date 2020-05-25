#ifndef MYPUSHBUTTON2_H
#define MYPUSHBUTTON2_H

#include <QWidget>
#include<QPushButton>

class mypushbutton2 : public QPushButton
{
    Q_OBJECT
public:
    //explicit mypushbutton2(QWidget *parent = nullptr);
    //构造函数 参数1  正常显示的图片路径   参数2   按下后显示的图片路径
    mypushbutton2(QString moneyImg, QString noImg="");

    //成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
    QString moneyImgPath;
    QString noImgPath;



signals:

public slots:
};

#endif // MYPUSHBUTTON2_H
