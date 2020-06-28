#ifndef SCENE1_H
#define SCENE1_H
#include"tower2.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QList>
#include"tower.h"
#include"towerposition.h"
#include"enemy.h"
#include<QtMath>
#include<QTimer>
#include"testing.h"
#include"waypoint.h"
#include"bullet2.h"
#include"enemy2.h"
#include<QSound>
#include<QMediaPlayer>
class Tower2;
class bullet;
class Bullet2;
class Tower3;
class scene1:public QMainWindow
{
     Q_OBJECT
public:
   explicit scene1(QWidget *parent = nullptr);
void paintEvent(QPaintEvent*);
void addWayPoints();

void mousePressEvent(QMouseEvent *);
bool canBuyTower1();
bool canBuyTower2();
void loadTowerPositions();
void getHpDamage(int damage = 1);
bool loadWave();
void removedBullet(bullet *Bullet);
void addBullet(bullet *Bullet);
void removedBullet1(Bullet2 *bullet);
void addBullet1(Bullet2 *bullet);
int accelerate();
void removedEnemy(enemy *Enemy);
    QList<enemy *> enemyList() const;
    void removedEnemy(enemy2 *Enemy2);
        QList<enemy2 *> enemyList2() const;
    void gameOver();

  void awardGold(int gold);
void start();
bool canlevelup();
private slots:
    void updateMap();
    void gameStart();
signals:
//告诉choose场景已返回
void scene1Back();
private:
QList<WayPoint *>		m_wayPointsList;
QList<Tower *>			m_towersList1;
QList<TowerPosition>	m_towerPositionsList;
QList<Tower2 *>			m_towersList2;
QList<enemy*>           m_enemyList;
QList<enemy2*>           m_enemyList2;
int                     m_waves;
QList<bullet *>			m_bulletList;
QList<Bullet2*>         m_bulletList2;
QList<Tower3*>          m_towersList3;
int                     m_playerHp;
bool                    m_gameEnded;
int						m_playrGold;
bool					m_gameWin;
QSound                 *m_bgm;
friend class choosescene;
};
#endif // SCENE1_H
