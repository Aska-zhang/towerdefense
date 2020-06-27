#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
class QMediaPlayer;

enum SoundType
{
    TowerPlaceSound,		// 放塔时的声音
    LifeLoseSound,			// 基地费血时的声音
    LaserShootSound,		// 打中敌人时的生意
    EnemyDestorySound		// 敌人升天时的声音
};

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);

    void startBGM();
    void playSound(SoundType soundType);

private:
    QMediaPlayer *backgroundMusic; // 只用来播放背景音乐
signals:

public slots:
};

#endif // AUDIOPLAYER_H
