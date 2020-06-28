#include "scene2.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include "waypoint.h"
#include <QColor>
#include<QEvent>
#include<QMouseEvent>
#include"enemy.h"
#include<QTimer>
#include"choosescene.h"
#include<QRect>
#include<QString>
#include<QFont>
#include"towerposition.h"
#include<QSound>
static const int TowerCost = 400;
static const int TowerCost2 = 300;
static const int Towerlevelup=200;
scene2::scene2(QWidget *parent) : QMainWindow(parent) , m_waves(0)
  , m_playerHp(3)
  , m_playrGold(2000)
  , m_gameEnded(false)
  , m_gameWin(false)
{
    this->setFixedSize(1080,810);
    this->setWindowIcon(QIcon(":/back/icon.jpg"));
    this->setWindowTitle("Play with Doraemon");
    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu=bar->addMenu("start");
    QAction * quitAction=startMenu->addAction("quit");
    //点击实现退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
     addWayPoints();
     loadTowerPositions();
     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
     timer->start(30);
     mypushbutton*backBtn=new mypushbutton(":/back/backbtn2.png");
     backBtn->setParent(this);
     backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
     //点击返回
     connect(backBtn,&mypushbutton::clicked,[=](){
         backBtn->zoom1();
          backBtn->zoom2();
         QTimer::singleShot(500,this,[=](){
            m_bgm->stop();
             emit this->scene2Back();
             //延时返回

         });

     });
}
void scene2:: paintEvent(QPaintEvent*)
{QSound*shengli=new QSound("qrc:/back/triumoh.wav");
    QSound*shibai=new QSound("qrc:/back/lose.wav");
    if (m_gameEnded || m_gameWin)
    {
        if(m_gameEnded==true&&m_gameWin==false)
      {
            QPixmap pic(":/back/you lose.png");

          QPainter painter(this);
           painter.drawPixmap(0, 0, pic);
           m_bgm->stop();
shibai->play();
    }
        if(m_gameWin==true&&m_gameEnded==false)
        {QPixmap pic(":/back/you win.png");
                   QPainter painter(this);
                    painter.drawPixmap(0, 0, pic);
                    m_bgm->stop();
                    shengli->play();
        }
        return;
    }
    QPixmap cachePix(":/back/background5.jpg");
    QPainter cachePainter(&cachePix);
    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);
    foreach (const Tower4 *tower, m_towersList)
        tower->draw(&cachePainter);
  foreach (enemy3 *Enemy, m_enemyList)
        Enemy->draw(&cachePainter);
    foreach (const Bullet3 *bullet, m_bulletList)
        bullet->draw(&cachePainter);



    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
    QFont font("Arial",10,QFont::Bold,true);
        painter.setFont(font);
        painter.setPen(QPen(Qt::black));
        painter.drawText(QRect(200, 50, 200, 50),Qt::AlignHCenter, QString("WAVE : %1/5").arg(m_waves + 1));

        painter.drawText(QRect(0, 50, 200, 50),Qt::AlignHCenter, QString("HP : %1/3").arg(m_playerHp));

        painter.drawText(QRect(400, 50, 200, 50), Qt::AlignHCenter,QString("GOLD : %1").arg(m_playrGold));


}
void scene2::addWayPoints()
{ WayPoint *wayPoint1 = new WayPoint(QPoint(930,252));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(595,252));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);
    WayPoint *wayPoint3 = new WayPoint(QPoint(595, 720));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);
    WayPoint *wayPoint4 = new WayPoint(QPoint(40, 720));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);


}
bool scene2::canBuyTower1()
{


        if (m_playrGold >= TowerCost)
            return true;
        return false;


}
bool scene2::canlevelup()
{


        if (m_playrGold >= Towerlevelup)
            return true;
        return false;


}
bool scene2::canBuyTower2()
{


        if (m_playrGold >= TowerCost2)
            return true;
        return false;


}
void scene2::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(410, 520),

       QPoint(93, 520),


       QPoint(410,220),

QPoint(735,690),


   QPoint(735,380),
        QPoint(655,80),
    QPoint(1, 1),
        QPoint(1, 2),
       QPoint(1, 3),
        QPoint(1, 4),
           QPoint(1, 5),
          QPoint(1, 6),
        QPoint(1, 7),
           QPoint(1, 8),
          QPoint(1, 9),
           QPoint(1, 10),
              QPoint(1, 11),
             QPoint(1, 12),
        QPoint(1, 13),
           QPoint(1, 14),
          QPoint(1, 15),
           QPoint(1, 16),
              QPoint(1, 17),
             QPoint(1, 18),
        QPoint(2, 27),
           QPoint(2, 28),
          QPoint(2, 29),
           QPoint(2, 30),
              QPoint(2, 31),
             QPoint(2, 32),
        QPoint(2, 33),
           QPoint(2, 34),
          QPoint(21, 35),
           QPoint(21, 36),
              QPoint(2, 37),
             QPoint(2, 38),
        QPoint(2, 27),
           QPoint(1, 28),
          QPoint(1, 29),
           QPoint(1, 30),
              QPoint(1, 31),
             QPoint(1, 32),
        QPoint(1, 33),
           QPoint(1, 34),
          QPoint(1, 35),
           QPoint(1, 36),
              QPoint(1, 37),
             QPoint(1, 38)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);

}
void scene2::start(){

QSound *bgm=new QSound("qrc:/back/music2.wav");
m_bgm=bgm;
m_bgm->setLoops(10);
m_bgm->play();
QTimer::singleShot(300, this, SLOT(gameStart()));



}
void scene2::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}
void scene2::mousePressEvent(QMouseEvent *event)
{QSound *bulletmusic=new QSound("qrc:/back/bullet.wav");
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
auto it2 = m_towerPositionsList.begin();
    if(event->button()==Qt::LeftButton)
    {
     while (it != m_towerPositionsList.end())
    {

        if (canBuyTower1() && it->containPoint(pressPos) && !it->hasTower())
        {bulletmusic->play();
            m_playrGold -= TowerCost;
            it->setHasTower();
            Tower4 *tower = new Tower4(it->centerPos(),this,1);
            m_towersList.push_back(tower);
            update();
            break;

        }


   foreach (Tower4*tower, m_towersList) {
            if( it->containPoint(pressPos)&&it->hasTower()&&tower->containPoint(pressPos)&&canlevelup())
            {
                if(tower->level()<=1)
                {
                    tower->levelup();
                m_playrGold-=200;
                }

        }

   }
   ++it;
    }}
    if(event->button()==Qt::RightButton)
    {
        while (it2 != m_towerPositionsList.end())
        {
            if (canBuyTower2() && it2->containPoint(pressPos) && !it2->hasTower())
        {bulletmusic->play();
            m_playrGold -= TowerCost2;
            it2->setHasTower();
            Tower4 *tower2 = new Tower4(it2->centerPos(),this,2);
            m_towersList.push_back(tower2);
            update();
            break;
        }




++it2;

}}

}
void scene2::keyPressEvent(QKeyEvent *event)

{
auto it = m_towerPositionsList.begin();
    if(event->key()==Qt::Key_D)
    {
 while (it != m_towerPositionsList.end())

   { foreach (Tower4*tower, m_towersList)
{ if(it->hasTower())
       {  m_towersList.removeOne(tower);
        if(tower->hasEnemy())
        tower->lostSightOfEnemy();
        delete tower;
        it->setHasTower(false);
        m_playrGold+=100;
    }
       } it++;
 }





}




}
void scene2::getHpDamage(int damage/* = 1*/)
{

    m_playerHp -= damage;
    if (m_playerHp <= 0)
        gameOver();
}
void scene2::gameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;

    }
}

void scene2::removedEnemy(enemy3 *Enemy)
{
    Q_ASSERT(Enemy);
    m_enemyList.removeOne(Enemy);
    delete Enemy;

        if (m_enemyList.empty())

        {++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;

        }
        }
}

void scene2::updateMap()
{
    foreach (enemy3 *Enemy, m_enemyList)
       Enemy->move();


    foreach (Tower4 *tower, m_towersList)
        tower->checkEnemyInRange();

    update();
}
bool scene2::loadWave()
{
    if (m_waves >=5)
        return false;
    WayPoint *startWayPoint = m_wayPointsList.back();
    int Interval[] = { 100,3000, 6000};
int Interval1[] = { 100,5000, 12000};

            for (int i = 0; i <3; ++i)
    {
        enemy3 *Enemy = new enemy3(startWayPoint,this,1);

        m_enemyList.push_back(Enemy);

        enemy3*Enemy2=new enemy3(startWayPoint,this,2);
        m_enemyList.push_back(Enemy2);
        QTimer::singleShot(Interval[i], Enemy, SLOT(doActivate()));
        QTimer::singleShot(Interval1[i], Enemy2, SLOT(doActivate()));

        }





    return true;
}

QList<enemy3 *> scene2::enemyList() const
{
    return m_enemyList;
}
void scene2::removedBullet(Bullet3 *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void scene2::addBullet(Bullet3 *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}
void scene2::gameStart()
{
    loadWave();
}
