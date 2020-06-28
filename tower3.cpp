#include "tower3.h"

#include "tower2.h"


#include "tower.h"
#include "enemy.h"

#include "mainwindow.h"
#include"testing.h"
#include"bullet.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include"collision.h"
const QSize Tower3::fixedSize(110, 90);
class scene1;
Tower3::Tower3(QPoint pos, scene1 *game,const QPixmap &sprite)
    : m_attacking(false)
    , m_attackRange(150)
    , m_damage(30)
    , m_fireRate(500)

    , m_chooseEnemy(NULL)
    , m_chooseEnemy2(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)

{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));

}

Tower3::~Tower3()
{

    delete m_fireRateTimer;
    m_fireRateTimer = NULL;

}

void Tower3::checkEnemyInRange()
{
    if(m_game->accelerate()%2==0)
    {
        if (m_chooseEnemy)
    {



        if (!collision(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        QList<enemy *> enemyList = m_game->enemyList();
        foreach (enemy *Enemy, enemyList)
        {
            if (collision(m_pos, m_attackRange, Enemy->pos(), 1))
            {
                chooseEnemyForAttack(Enemy);
                break;
            }
        }
        }
    }
    if(m_game->accelerate()%2!=0){
    if (m_chooseEnemy2)
    {



        if (!collision(m_pos, m_attackRange, m_chooseEnemy2->pos(), 1))
            lostSightOfEnemy2();
    }
    else
    {

        QList<enemy2 *> enemyList2 = m_game->enemyList2();
        foreach (enemy2 *Enemy2, enemyList2)
        {
            if (collision(m_pos, m_attackRange, Enemy2->pos(), 1))
            {
                chooseEnemyForAttack(Enemy2);
                break;
            }
        }
    }
}
}



void Tower3::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::lightGray);

    painter->drawEllipse(m_pos,150,150);


    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);

    painter->translate(m_pos);

    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Tower3::attackEnemy()
{

    m_fireRateTimer->start(m_fireRate);

}
void Tower3::chooseEnemyForAttack(enemy *Enemy)
{

    m_chooseEnemy = Enemy;

    attackEnemy();

    m_chooseEnemy->getAttacked(this);
}
void Tower3::chooseEnemyForAttack(enemy2 *Enemy2)
{

    m_chooseEnemy2 = Enemy2;

    attackEnemy();

    m_chooseEnemy2->getAttacked(this);
}
void Tower3::shootWeapon()
{

    if(m_game->accelerate()%2==0)
    {Bullet2 *bullet = new Bullet2(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet1(bullet);
}
    if(m_game->accelerate()%2!=0)
    {
        Bullet2 *bullet = new Bullet2(m_pos, m_chooseEnemy2->pos(), m_damage, m_chooseEnemy2, m_game);
            bullet->move();
            m_game->addBullet1(bullet);
    }
}
void Tower3::targetKilled()
{

    if(m_game->accelerate()%2==0)
    {if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();

    }
}
void Tower3::targetKilled2()
{if(m_game->accelerate()%2!=0)
    {if (m_chooseEnemy2)
        m_chooseEnemy2 = NULL;
    m_fireRateTimer->stop();

}}
void Tower3::lostSightOfEnemy2()
{

  if(m_game->accelerate()%2!=0)
   { m_chooseEnemy2->gotLostSight(this);
    if (m_chooseEnemy2)
        m_chooseEnemy2 = NULL;
    m_fireRateTimer->stop();

}
}
void Tower3::lostSightOfEnemy()
{
   if(m_game->accelerate()%2==0)
   { m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();

   }
}
