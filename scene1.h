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
class WayPoint;
class enemy;
class scene1:public QMainWindow
{
     Q_OBJECT;
public:
    explicit scene1(QWidget *parent = nullptr);
void paintEvent(QPaintEvent*);
void addWayPoints();

void mousePressEvent(QMouseEvent *);
bool canBuyTower();
void loadTowerPositions();
void getHpDamage(int damage = 1);
bool loadWave();

void removedEnemy(enemy *Enemy);
    QList<enemy *> enemyList() const;

private slots:
    void updateMap();
    void gameStart();
private:
QList<WayPoint *>		m_wayPointsList;
QList<Tower *>			m_towersList1;
QList<TowerPosition>	m_towerPositionsList;
QList<Tower2*>          m_towersList2;
QList<enemy*>           m_enemyList;
int                     m_waves;

};

#endif // SCENE1_H
