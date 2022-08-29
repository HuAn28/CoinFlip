#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // 构造函数 参数1:正常显示的图片路径 参数2:按下后显示的图片路径
    MyPushButton(QString normalImg, QString pressImg = "");

    // 成员属性 保存用户传入的默认显示路径以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    // 弹跳特效
    void zoom1();  // 向下跳
    void zoom2();  // 向上跳

    // 重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
