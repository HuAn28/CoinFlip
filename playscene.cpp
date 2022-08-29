#include "playscene.h"

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;

    // 初始化游戏场景
    // 设置固定大小
    this->setFixedSize(320,500) ;
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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

    // 返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);
    // 翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav", this);
    // 胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav", this);

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &MyPushButton::clicked, [=](){
        qDebug() << "点击了返回按钮";
        backSound->play();
        // 告诉游戏选择场景 我返回了，游戏选择场景监听chooseLevelScene的返回按钮
        emit this->chooseSceneBack();
    });

    // 显示当前关卡数
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(20);
    QString str1 = QString("Level:%1").arg(this->levelIndex);
    qDebug() << str1;
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50, 140, 50);

    // 胜利图像绘制
    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());

    dataConfig config;
    // 初始化每个关卡的二维数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    // 显示金币背景图案
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++)
        {
            // 绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i * 50, 157 + j * 50);

            // 创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                // 显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(60 + i * 50, 160 + j * 50);

            // 给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];  // 1金币 0银币
            coin->isWin = false;

            // 将金币放入到二维数组 以便后期的维护
            coinBtn[i][j] = coin;

            // 点击金、银币进行翻转
            connect(coin, &MyCoin::clicked, [=](){
                flipSound->play();
                for(int i = 0; i < 4;i ++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }
               coin->changeFlag();
               this->gameArray[i][j] = !this->gameArray[i][j];

               // 翻转周围硬币
               // 周围延时翻转
               QTimer::singleShot(300, this, [=](){
                   if(coin->posX + 1 <= 3) // 金币的右侧金币翻转条件
                   {
                       coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX + 1][coin->posY] = !this->gameArray[coin->posX + 1][coin->posY];
                   }
                   if(coin->posX - 1 >= 0) // 金币的左侧金币翻转条件
                   {
                       coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX - 1][coin->posY] = !this->gameArray[coin->posX - 1][coin->posY];
                   }
                   if(coin->posY + 1 <= 3) // 金币的上侧金币翻转条件
                   {
                       coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY + 1] = !this->gameArray[coin->posX][coin->posY + 1];
                   }
                   if(coin->posY - 1 >= 0) // 金币的下侧金币翻转条件
                   {
                       coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY - 1] = !this->gameArray[coin->posX][coin->posY - 1];
                   }

                   // 翻完所有金币后 解开所有金币禁用
                   for(int i = 0; i < 4;i ++)
                   {
                       for(int j = 0; j < 4; j++)
                       {
                           this->coinBtn[i][j]->isWin = false;
                       }
                   }

                   // 判断是否胜利
                   this->isWin = true;
                   for(int i = 0; i < 4;i ++)
                   {
                       for(int j = 0; j < 4; j++)
                       {
                           if(coinBtn[i][j]->flag == false) {  // 只要有一个是反面，那就算失败
                               this->isWin = false;
                               break;
                           }
                       }
                   }
                   if(this->isWin == true)
                   {
                       winSound->play();
                       for(int i = 0; i < 4;i ++)
                       {
                           for(int j = 0; j < 4; j++)
                           {
                               coinBtn[i][j]->isWin = true;
                           }
                       }

                       // 将胜利的图片从上往下移动
                       QPropertyAnimation *animation = new QPropertyAnimation(winLabel, "geometry");
                       // 设置时间间隔
                       animation->setDuration(1000);
                       // 设置开始位置
                       animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                       // 设置结束位置
                       animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 134, winLabel->width(), winLabel->height()));
                       // 设置曲线
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       // 执行动画
                       animation->start();
                   }
               });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);  // 图片自动拉伸适应屏幕

    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);  // 宽高变成原来的0.5
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
