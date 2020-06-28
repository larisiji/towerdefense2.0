#include "enemy3.h"
#include "waypoint.h"
#include "tower4.h"
#include"collision.h"
#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 100;
class scene2;
const QSize enemy3::ms_fixedSize(80, 150);

enemy3::enemy3(WayPoint *startWayPoint, scene2 *game,int type)
    : QObject(0)
    , m_active(false)
,m_type(type)
    , m_rotationSprite(90.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    ,m_game(game)



{
    const QPixmap &m1=QPixmap(":/back/enemy4.0.png");
  if(m_type==1)
 { m_sprite=QPixmap(m1);
      m_walkingSpeed=5;
      m_currentHp=50*game->wave();
      m_maxHp=50*game->wave();
  }
  if(m_type==2)
  {m_sprite=QPixmap(":/back/enemy7.0.png");
      m_walkingSpeed=4;
      m_currentHp=30*game->wave();
      m_maxHp=30*game->wave();}


}

enemy3::~enemy3()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void enemy3::doActivate()
{

    m_active = true;
}

void enemy3::move()
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

void enemy3::draw(QPainter *painter) const
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


void enemy3::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;


    foreach (Tower4 *attacker, m_attackedTowersList)
        attacker->targetKilled();

    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void enemy3::getDamage(int damage,bool speed)
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


void enemy3::getAttacked(Tower4 *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

void enemy3::gotLostSight(Tower4 *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}


QPoint enemy3::pos() const
{
    return m_pos;
}

