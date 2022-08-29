#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    /* 选择关卡场景 */
    // 设置固定大小
    this->setFixedSize(320, 500);
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    this->setWindowTitle("选择关卡场景");

    // 创建菜单栏
    QMenuBar *menubar= menuBar();
    setMenuBar(menubar);
    // 创建开始菜单
    QMenu *menuStart = menubar->addMenu("开始");
    // 创建退出菜单项
    QAction *actionQuit = menuStart->addAction("退出");
    // 点击退出实现退出游戏
    connect(actionQuit, &QAction::triggered, [=](){
        this->close();
    });

    // 选择关卡按钮音效
    chooseSound = new QSound(":/res/TapButtonSound.wav", this);
    // 返回按钮音效
    backSound = new QSound(":/res/BackButtonSound.wav", this);

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &MyPushButton::clicked, [=](){
        qDebug() << "点击了返回按钮";
        backSound->play();
        // 告诉主场景 我返回了，主场景监听chooseLevelScene的返回按钮
        emit this->chooseSceneBack();
    });

    // 创建选择关卡的按钮
    for(int i = 0; i < 20; i++) {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        // 监听每隔按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=](){
            chooseSound->play();
            QString str = QString("您选择的是第%1关").arg(i + 1);
            qDebug() << str;

            // 进入到游戏场景
            this->hide();  // 将选关场景隐藏掉
            play = new PlayScene(i + 1);  // 创建游戏场景
            // 设置游戏场景初始位置
            play->setGeometry(this->geometry());
            play->show();  // 显示游戏场景

            connect(play, &PlayScene::chooseSceneBack, [=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = nullptr;
            });
        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        // 设置label上的文字对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        // 设置让鼠标进行穿透51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    // 背景
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);  // 图片自动拉伸适应屏幕
    // 标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
