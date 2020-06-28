#include "scene1.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include "waypoint.h"
QList<WayPoint *> m_wayPointsList;
#include <QColor>
#include<QEvent>
#include<QMouseEvent>
#include"tower2.h"
#include"enemy.h"
#include<QTimer>
#include"choosescene.h"
#include<QRect>
#include<QString>
#include<QFont>
#include"tower3.h"
#include"towerposition.h"
#include<QSound>
#include<QMediaPlayer>
static const int TowerCost = 400;
static const int TowerCost2 = 300;
static const int Towerlevelup=500;
scene1::scene1(QWidget *parent) : QMainWindow(parent)

  , m_waves(0)
  , m_playerHp(10)
  , m_playrGold(2000)
  , m_gameEnded(false)
  , m_gameWin(false)

{
    //配置选择关卡场景
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
        emit this->scene1Back();
        //延时返回

    });

});
}

void scene1::start(){
QSound*bgm= new QSound("qrc:/back/music.wav");
m_bgm=bgm;
m_bgm->setLoops(10);

m_bgm->play();
QTimer::singleShot(300, this, SLOT(gameStart()));
/*if(m_gameEnded==true)
{
    mypushbutton * backBtn1=new mypushbutton( ":/back/1.png");
  backBtn1->setParent(this);
 backBtn1->move((int)(this->width()*0.445),(int)(this->height()*0.2));
 choosescene *choice2=new choosescene;
connect(backBtn1,&mypushbutton::clicked,[=](){
    backBtn1->zoom1();
    backBtn1->zoom2();
    QTimer::singleShot(500,this,[=](){
        this->hide();
        choice2->show();
});

   });
}*/
}
void scene1:: paintEvent(QPaintEvent*)
{QSound*shibai=new QSound("qrc:/back/lose.wav");
    QSound*shengli=new QSound("qrc:/back/triumoh.wav");
    if (m_gameEnded || m_gameWin)
    {
        if(m_gameEnded==true)
      {
            QPixmap pic(":/back/you lose.png");

m_bgm->stop();shibai->play();
          QPainter painter(this);
           painter.drawPixmap(0, 0, pic);

    }
        if(m_gameWin==true)
        {QPixmap pic(":/back/you win.png");
                   QPainter painter(this);
                    painter.drawPixmap(0, 0, pic);
                    m_bgm->stop();
                    shengli->play();
        }
        return;
    }

    QPixmap cachePix(":/back/background.jpg");
    QPainter cachePainter(&cachePix);
    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);
    foreach (const Tower *tower, m_towersList1)
        tower->draw(&cachePainter);

    foreach (const Tower2 *tower2, m_towersList2)
        tower2->draw(&cachePainter);
    foreach (const Tower3 *tower3, m_towersList3)
        tower3->draw(&cachePainter);
  if(m_waves%2==0)
 {   foreach (enemy *Enemy, m_enemyList)
        Enemy->draw(&cachePainter);
}
  if(m_waves%2!=0)
 {       foreach (enemy2 *Enemy2, m_enemyList2)
        Enemy2->draw(&cachePainter);
}
    foreach (const bullet *Bullet, m_bulletList)
        Bullet->draw(&cachePainter);
    foreach (const Bullet2 *bullet, m_bulletList2)
        bullet->draw(&cachePainter);


    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
    QFont font("Arial",20,QFont::Bold,true);
        painter.setFont(font);
        painter.setPen(QPen(Qt::black));
        painter.drawText(QRect(700, 750, 300, 50),Qt::AlignHCenter, QString("WAVE : %1/20").arg(m_waves + 1));

        painter.drawText(QRect(100, 750, 300, 50),Qt::AlignHCenter, QString("HP : %1/10").arg(m_playerHp));

        painter.drawText(QRect(400, 750, 300, 50), Qt::AlignHCenter,QString("GOLD : %1").arg(m_playrGold));








}
void scene1::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}
void scene1::addWayPoints()
{ WayPoint *wayPoint1 = new WayPoint(QPoint(880,550));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(830,550));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);
    WayPoint *wayPoint3 = new WayPoint(QPoint(830, 440));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);
    WayPoint *wayPoint4 = new WayPoint(QPoint(445, 440));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(445, 550));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);
    WayPoint *wayPoint6 = new WayPoint(QPoint(35, 550));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
    WayPoint *wayPoint7 = new WayPoint(QPoint(35, 230));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(480, 230));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);
}







void scene1::mousePressEvent(QMouseEvent *event)

{QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    auto it2=m_towerPositionsList.begin();

    if(event->button()==Qt::LeftButton)
    {
        while(it2!=m_towerPositionsList.end())
     {
            if ( it2->containPoint(pressPos) && it2->hasTower()&&canlevelup()) {
       m_playrGold -= Towerlevelup;

       Tower3*tower3=new Tower3(it2->centerPos(),this);
       m_towersList3.push_back(tower3);

       update();
       break;
     }
            ++it2;
        }
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower1() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_playrGold -= TowerCost;
            it->setHasTower();
            Tower *tower = new Tower(it->centerPos(),this);
            m_towersList1.push_back(tower);
            update();

            break;
        }

        ++it;
    }




    }

    if(event->button()==Qt::RightButton)
    {

    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower2() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_playrGold -= TowerCost2;
            it->setHasTower();
            Tower2 *tower2 = new Tower2(it->centerPos(),this);
            m_towersList2.push_back(tower2);
            update();
            break;
        }

        ++it;
    }}

    }

void scene1::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(380, 90),

       QPoint(60, 90),


       QPoint(250,300),

QPoint(220,650),


   QPoint(120,410),
        QPoint(510,520)
      //  QPoint(170, 35),
      //  QPoint(260, 35),
     //   QPoint(350, 35)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);

}
bool scene1::canBuyTower1()
{


        if (m_playrGold >= TowerCost)
            return true;
        return false;


}
bool scene1::canlevelup()
{


        if (m_playrGold >= Towerlevelup)
            return true;
        return false;


}
bool scene1::canBuyTower2()
{


        if (m_playrGold >= TowerCost2)
            return true;
        return false;


}
void scene1::getHpDamage(int damage/* = 1*/)
{

    m_playerHp -= damage;
    if (m_playerHp <= 0)
        gameOver();
}
void scene1::gameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;

    }
}

void scene1::removedEnemy(enemy *Enemy)
{if(m_waves%2==0)
    {Q_ASSERT(Enemy);
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


}
void scene1::removedEnemy(enemy2 *Enemy2)
{if(m_waves%2!=0)
   { Q_ASSERT(Enemy2);
    m_enemyList2.removeOne(Enemy2);
    delete Enemy2;

       if (m_enemyList2.empty())

        {++m_waves;

              if (!loadWave())
              {
                  m_gameWin = true;

              }
          }
}
}
void scene1::updateMap()
{if(m_waves%2==0)
 {   foreach (enemy *Enemy, m_enemyList)
       Enemy->move();
}
    if(m_waves%2!=0)
 {   foreach (enemy2 *Enemy2, m_enemyList2)
       Enemy2->move();
}
    foreach (Tower *tower, m_towersList1)
        tower->checkEnemyInRange();
    foreach (Tower2 *tower2, m_towersList2)
        tower2->checkEnemyInRange();
    foreach (Tower3 *tower3, m_towersList3)
        tower3->checkEnemyInRange();
    update();
}
bool scene1::loadWave()
{
    if (m_waves >=20)
        return false;
    WayPoint *startWayPoint = m_wayPointsList.back();
    int Interval[] = { 100,3000, 6000, 11000,15000, 18000,21000};
int Interval1[] = { 100,5000, 12000,15000};
        if(m_waves%2==0)
        {
            for (int i = 0; i <7; ++i)
    {
        enemy *Enemy = new enemy(startWayPoint,this);
        m_enemyList.push_back(Enemy);

        QTimer::singleShot(Interval[i], Enemy, SLOT(doActivate()));
            }
        }
        if(m_waves%2!=0)
        {
            for (int i = 0; i <4; ++i)
          {  enemy2 *Enemy2 = new enemy2(startWayPoint,this);
        m_enemyList2.push_back(Enemy2);
        QTimer::singleShot(Interval1[i], Enemy2, SLOT(doActivate()));
          }
        }



    return true;
}

QList<enemy *> scene1::enemyList() const
{
    return m_enemyList;
}
QList<enemy2 *> scene1::enemyList2() const
{
    return m_enemyList2;
}
void scene1::gameStart()
{
    loadWave();
}


void scene1::removedBullet(bullet *Bullet)
{
    Q_ASSERT(Bullet);

    m_bulletList.removeOne(Bullet);
    delete Bullet;
}

void scene1::addBullet(bullet *Bullet)
{
    Q_ASSERT(Bullet);

    m_bulletList.push_back(Bullet);
}
void scene1::removedBullet1(Bullet2 *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList2.removeOne(bullet);
    delete bullet;
}

void scene1::addBullet1(Bullet2 *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList2.push_back(bullet);
}
int scene1:: accelerate()
{

    return m_waves;
}

