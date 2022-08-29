#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QSound>
#include "mypushbutton.h"
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent *);

public:
    ChooseLevelScene *chooseScene = NULL;
    QSound *startSound;

private slots:
    void on_actionQuit_triggered();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
