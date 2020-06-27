#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevel.h"


namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();

    void paintEvent(QPaintEvent *);
    AudioPlayer * audioPlayer;

    chooselevel *choosescene = NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
