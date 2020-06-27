#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>

static const QString s_curDir = QDir::currentPath() + "/";
AudioPlayer::AudioPlayer(int tagg,QObject *parent) : QObject(parent), backgroundMusic(nullptr),tag(tagg)
{
    // 创建一直播放的背景音乐"qrc:/music/BGMusic.mp3"
    QString q;
    if(tag==1)
        {q="qrc:/music/BGMusic.mp3";}
    else {
//        q="qrc:/music/sparkle.mp3";
        q="qrc:/music/BGM.mp3";
    }

//    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + q);
    QUrl backgroundMusicUrl = QUrl(q);
//    backgroundMusic->setMedia(backgroundMusicUrl);
//    backgroundMusic->setVolume(50);
//    if (QFile::exists(backgroundMusicUrl.toLocalFile()))
//    {
        backgroundMusic = new QMediaPlayer(this);
        QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();
//        backgroundMusic->setMedia(backgroundMusicUrl);
        QMediaContent media(backgroundMusicUrl);
        backgroundMusicList->addMedia(media);
        backgroundMusicList->setCurrentIndex(0);
        // 设置背景音乐循环播放
        backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        backgroundMusic->setPlaylist(backgroundMusicList);
            backgroundMusic->setVolume(50);
//    }
}

void AudioPlayer::startBGM()
{


    if (backgroundMusic)
        backgroundMusic->play();

}


void AudioPlayer::stopBGM()
{


    if (backgroundMusic)
        backgroundMusic->stop();

}
void AudioPlayer::playSound(SoundType soundType)
{
    static const QUrl mediasUrls[] =
    {
//        QUrl::fromLocalFile(s_curDir + "music/TowerBuild.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/BigBoss.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/Bottle.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/Pin.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/Pstar.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/Fat142.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/Towerupdata.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/TowerSelect.mp3"),
//        QUrl::fromLocalFile(s_curDir + "music/TowerSell.mp3"),
        QUrl("qrc:/music/TowerBulid.mp3"),
        QUrl("qrc:/music/BigBoss.mp3"),
        QUrl("qrc:/music/bottle.mp3"),
        QUrl("qrc:/music/pin.mp3"),
        QUrl("qrc:/music/PStar.mp3"),
        QUrl("qrc:/music/Fat142.mp3"),
        QUrl("qrc:/music/TowerUpdata.mp3"),
        QUrl("qrc:/music/TowerSelect.mp3"),
        QUrl("qrc:/music/TowerSell.mp3"),
    };
    static QMediaPlayer player;

//    if (QFile::exists(mediasUrls[soundType].toLocalFile()))
//    {
        player.setMedia(mediasUrls[soundType]);
        player.play();
//    }
}
