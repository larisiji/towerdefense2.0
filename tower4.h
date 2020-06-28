#ifndef TOWER4_H
#define TOWER4_H


#include <QObject>
#include <QWidget>
#include"scene2.h"
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include"enemy.h"
#include"enemy2.h"
#include"testing.h"
#include"enemy3.h"
#include"scene2.h"
class MainWindow;
class QTimer;
class QPainter;
class Tower4 : QObject
{
    Q_OBJECT
public:
    Tower4(QPoint pos, scene2*game,int type);
    ~Tower4();

    void draw(QPainter *painter) const;

 static const QSize fixedSize;

 void attackEnemy();

 void chooseEnemyForAttack(enemy3 *Enemy);
 void targetKilled();
bool hasEnemy();
 void lostSightOfEnemy();
void checkEnemyInRange();


  bool containPoint(const QPoint &pos) const;
void levelup();
int level();
private slots:

 void shoot();

private:
 bool			m_attacking;
 int				m_attackRange;	// 代表塔可以攻击到敌人的距离
 int				m_damage;		// 代表攻击敌人时造成的伤害
 int				m_fireRate;		// 代表再次攻击敌人的时间间隔


 enemy3 *			m_chooseEnemy;
 scene2 *	m_game;
 QTimer *		m_fireRateTimer;
int m_type;

    const QPoint	m_pos;
     QPixmap	m_sprite;
int m_level;
};

#endif // TOWER4_H
