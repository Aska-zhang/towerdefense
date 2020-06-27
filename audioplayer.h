#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
class QMediaPlayer;

enum SoundType
{
    TowerBuild,		// 放塔时的声音
    BigBoss,			// 基地费血时的声音
    bottle,	         // 打中敌人时的生意
    pin,
    Pstar,
    Fat142,		// 敌人升天时的声音
    Towerupdata,     //升级塔
    Towerselect ,
    TowerSell//选择塔
};

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(int tagg,QObject *parent = nullptr);

    void startBGM();
    void stopBGM();
    void playSound(SoundType soundType);

private:
    QMediaPlayer *backgroundMusic; // 只用来播放背景音乐
    int tag;//tag为1表示主页面，为2表示战斗页面
signals:

public slots:
};

#endif // AUDIOPLAYER_H
