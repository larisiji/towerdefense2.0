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
scene1::scene1(QWidget *parent) : QMainWindow(parent)
{
     m_waves=0;
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

QTimer::singleShot(300, this, SLOT(gameStart()));

}
void scene1:: paintEvent(QPaintEvent*)
{

    QPixmap cachePix(":/back/background.jpg");
    QPainter cachePainter(&cachePix);
    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);
    foreach (const Tower *tower, m_towersList1)
        tower->draw(&cachePainter);
    foreach (const Tower2 *tower2, m_towersList2)
        tower2->draw(&cachePainter);

    foreach (enemy *Enemy, m_enemyList)
        Enemy->draw(&cachePainter);
    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);

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
    if(event->button()==Qt::LeftButton)
    {

    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            it->setHasTower();
            Tower *tower = new Tower(it->centerPos());
            m_towersList1.push_back(tower);
            update();
            break;
        }

        ++it;
    }}
    if(event->button()==Qt::RightButton)
    {
        while (it != m_towerPositionsList.end())
        {
            if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
            {
                it->setHasTower();
                Tower2 *tower2 = new Tower2(it->centerPos());
                m_towersList2.push_back(tower2);
                update();
                break;
            }

            ++it;
        }
    }

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
bool scene1::canBuyTower()
{
    return true;
}

void scene1::getHpDamage(int damage)
{

}
void scene1::removedEnemy(enemy *Enemy)
{
    Q_ASSERT(Enemy);
    m_enemyList.removeOne(Enemy);
    delete Enemy;
    if (m_enemyList.empty())
    {
        ++m_waves;

    }
}
void scene1::updateMap()
{
    foreach (enemy *Enemy, m_enemyList)
       Enemy->move();
    update();
}
bool scene1::loadWave()
{
    if (m_waves >=7)
        return false;
    WayPoint *startWayPoint = m_wayPointsList.back();
    int Interval[] = { 100,4000, 8000, 12000,15000, 20000,35000 };
    for (int i = 0; i <7; ++i)
    {
        enemy *Enemy = new enemy(startWayPoint);
        m_enemyList.push_back(Enemy);

        QTimer::singleShot(Interval[i], Enemy, SLOT(doActivate()));
    }
    return true;
}
QList<enemy *> scene1::enemyList() const
{
    return m_enemyList;
}

void scene1::gameStart()
{
    loadWave();
}
