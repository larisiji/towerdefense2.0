#include "enemy.h"

#include "waypoint.h"
#include "tower.h"
#include"collision.h"
#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include"tower3.h"
#include"tower2.h"
static const int Health_Bar_Width = 100;
class scene1;
const QSize enemy::ms_fixedSize(80, 150);

enemy::enemy(WayPoint *startWayPoint, scene1 *game,const QPixmap &sprite/* = QPixmap(":/back/enemy1.png")*/)
    : QObject(0)
    , m_active(false)

, m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    ,m_game(game)
    , m_sprite(sprite)
{
    if(game->accelerate()<6)
       { m_walkingSpeed=3.0;
        m_maxHp=200;
        m_currentHp=200;
       }
    if(game->accelerate()==6)
    {m_walkingSpeed=4;
        m_maxHp=300;
        m_currentHp=300;
    }
    if(game->accelerate()>6&&game->accelerate()<=12)
       {
        m_maxHp=200;
        m_currentHp=200;
        m_walkingSpeed=6;
    }
    if(game->accelerate()>13)
       {
        m_maxHp=300;
        m_currentHp=300;
        m_walkingSpeed=6.5;
       }

}

enemy::~enemy()
{
    m_attackedTowersList.clear();
    m_attackedTowersList2.clear();
     m_attackedTowersList3.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void enemy::doActivate()
{

    m_active = true;
}

void enemy::move()
{
    if (m_active!=true)
        return;

    if (collision(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {

        if (m_destinationWayPoint->nextWayPoint())
        {

            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {

            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }


    QPoint target= m_destinationWayPoint->pos();



   double Speed = m_walkingSpeed;
    QVector2D normalized(target - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * Speed;

 m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;

}

void enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
 painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}


void enemy::getRemoved()
{
    if (m_attackedTowersList.empty()&&m_attackedTowersList2.empty()&&m_attackedTowersList3.empty())
        return;


    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    foreach (Tower2 *attacker2, m_attackedTowersList2)
        attacker2->targetKilled();
    foreach (Tower3 *attacker3, m_attackedTowersList3)
        attacker3->targetKilled();

    m_game->removedEnemy(this);
}

void enemy::getDamage(int damage,bool speed)
{
    m_currentHp -= damage;
    if (m_currentHp <= 0)
    {
        m_game->awardGold(100);
        getRemoved();
    }
    else
   {
        if(speed)
        m_walkingSpeed=4.0;

    }


}


void enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}
void enemy::getAttacked(Tower3 *attacker2)
{
    m_attackedTowersList3.push_back(attacker2);
}

void enemy::getAttacked1(Tower2 *attacker1)
{
    m_attackedTowersList2.push_back(attacker1);
}
void enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}
void enemy::gotLostSight(Tower3 *attacker2)
{
    m_attackedTowersList3.removeOne(attacker2);
}
void enemy::gotLostSight1(Tower2 *attacker1)
{
    m_attackedTowersList2.removeOne(attacker1);
    m_walkingSpeed=3.0;
}


QPoint enemy::pos() const
{
    return m_pos;
}
