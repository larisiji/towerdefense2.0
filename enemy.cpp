#include "enemy.h"

#include "waypoint.h"
#include "tower.h"
#include"collision.h"
#include "mainwindow.h"
#include"scene1.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 100;

const QSize enemy::ms_fixedSize(80, 150);

enemy::enemy(WayPoint *startWayPoint, const QPixmap &sprite/* = QPixmap(":/back/enemy1.png")*/)
    : QObject(0)
    , m_active(false)
    , m_maxHp(40)
    , m_currentHp(40)
    , m_walkingSpeed(1.5)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())

    , m_sprite(sprite)
{
}

enemy::~enemy()
{

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
        // 敌人抵达了一个点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
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




void enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

QPoint enemy::pos() const
{
    return m_pos;
}
