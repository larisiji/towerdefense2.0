#ifndef TOWER2_H
#define TOWER2_H
#include"tower.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QPoint>
#include <QPixmap>
#include <QObject>
#include"scene1.h"
class scene1;
class enemy;
class enemy2;
class Tower2  : QObject
{

    Q_OBJECT
public:
    Tower2(QPoint pos, scene1*game,const QPixmap &sprite = QPixmap(":/back/airtrue.png"));
    ~Tower2();

    void draw(QPainter *painter) const;

 static const QSize fixedSize;

 void attackEnemy();

 void chooseEnemyForAttack(enemy *Enemy);
 void targetKilled();
void chooseEnemyForAttack(enemy2 *Enemy2);
 void lostSightOfEnemy();
void checkEnemyInRange();
 void lostSightOfEnemy2();
  void targetKilled2();
private slots:

 void shootWeapon();

private:
 bool			m_attacking;
 int				m_attackRange;	// 代表塔可以攻击到敌人的距离
 int				m_damage;		// 代表攻击敌人时造成的伤害
 int				m_fireRate;		// 代表再次攻击敌人的时间间隔

enemy2*          m_chooseEnemy2;
 enemy *			m_chooseEnemy;
 scene1 *	m_game;
 QTimer *		m_fireRateTimer;


    const QPoint	m_pos;
    const QPixmap	m_sprite;
};

#endif // TOWER2_H
