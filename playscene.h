#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelNum);
    // 重写paintEvent事件
    void paintEvent(QPaintEvent *);

public:
    int levelIndex;  // 内部成员 属性记录所选的关卡
    int gameArray[4][4];  // 二维数组 维护每个关卡的具体数据
    MyCoin *coinBtn[4][4];
    // 是否胜率的标志
    bool isWin;

signals:
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
