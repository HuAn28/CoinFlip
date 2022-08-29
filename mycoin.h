#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QDebug>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // 参数代表传入的金币路径还是银币路径
    MyCoin(QString btnImg);
    void changeFlag();
    // 重写按下函数
    void mousePressEvent(QMouseEvent *e);

public:
    // 金币的属性
    int posX;  // x坐标位置AA
    int posY;  // y坐标位置
    bool flag; // 正反标识
    QTimer *timer1;  // 金币翻银币的定时器
    QTimer *timer2;  // 银币翻金币的定时器
    int min = 1;
    int max = 8;
    // 执行动画 标志
    bool isAnimation = false;
    // 是否胜率的标志
    bool isWin;

signals:

};

#endif // MYCOIN_H
