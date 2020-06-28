#ifndef SCENE2_H
#define SCENE2_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QList>
#include"towerposition.h"
#include"enemy.h"
#include<QtMath>
#include<QTimer>
#include"tower4.h"
#include"waypoint.h"
#include"bullet3.h"
#include"enemy3.h"
#include<QSound>
class Tower4;
class  Bullet3;
class scene2:public QMainWindow
{
    Q_OBJECT
public:
    explicit scene2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void addWayPoints();
void mousePressEvent(QMouseEvent *);
    bool canBuyTower1();
    bool canBuyTower2();
    void loadTowerPositions();
    void getHpDamage(int damage = 1);
    bool loadWave();
    void removedBullet(Bullet3 *bullet);
    void addBullet(Bullet3 *bullet);
    void removedEnemy(enemy3*Enemy);
        QList<enemy3 *> enemyList() const;
        void gameOver();
      void awardGold(int gold);
    void start();
    bool canlevelup();
    void keyPressEvent(QKeyEvent *event);
   int wave(){return m_waves+1;}
private slots:
    void updateMap();
    void gameStart();
signals:
//告诉choose场景已返回
void scene2Back();
    private:
    QList<WayPoint *>		m_wayPointsList;
    QList<Tower4 *>			m_towersList;
    QList<TowerPosition>	m_towerPositionsList;

    QList<enemy3*>           m_enemyList;

    int                     m_waves;

    QList<Bullet3*>         m_bulletList;
    int                     m_playerHp;
    bool                    m_gameEnded;
    int						m_playrGold;
    bool					m_gameWin;
QSound *m_bgm;
    friend class choosescene;
    };



#endif // SCENE2_H
