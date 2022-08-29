#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    /* 配置主场景 */
    // 设置固定大小
    setFixedSize(320, 500);
    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    // 设置标题
    setWindowTitle("翻金币主场景");

    // 准备开始按钮的音效
    startSound = new QSound(":/res/TapButtonSound.wav", this);

    // 开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    chooseScene = new ChooseLevelScene;

    // 监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide(); // 将选择关卡场景隐藏掉
        this->show();  // 重新显示主场景
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
       qDebug() << "点击了开始";
       // 播放开始音效资源
       startSound->play();
       // 弹起特效
       startBtn->zoom1();
       startBtn->zoom2();

       // 进入到选择关卡场景中
       // 延时进入到选择关卡场景中
       QTimer::singleShot(500, this, [=](){
           chooseScene->setGeometry(this->geometry());
           // 自身隐藏
           this->hide();
           // 显示选择关卡场景
           chooseScene->show();
       });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    // 背景
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);  // 图片自动拉伸适应屏幕
    // 图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);  // 宽高变成原来的0.5
    painter.drawPixmap(10, 30, pix);
}


void MainScene::on_actionQuit_triggered()
{
    this->close();
}
