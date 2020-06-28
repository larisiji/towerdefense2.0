#include "bullet2.h"
#include "testing.h"
#include "enemy.h"
#include "scene1.h"
#include <QPainter>
#include <QPropertyAnimation>
#include"enemy2.h"
const QSize Bullet2::fixedSize(8, 8);

Bullet2::Bullet2(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
               scene1 *game, const QPixmap &sprite)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
{
}
Bullet2::Bullet2(QPoint startPos, QPoint targetPoint, int damage, enemy2 *target,
               scene1 *game, const QPixmap &sprite)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target2(target)
    , m_game(game)
    , m_damage(damage)
{
}
void Bullet2::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet2::move()
{

    static const int duration = 500;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet2::hitTarget()
{if(m_game->accelerate()%2==0)

    {if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(m_damage,true);}
    if(m_game->accelerate()%2!=0)
    {if (m_game->enemyList2().indexOf(m_target2) != -1)
        m_target2->getDamage(m_damage,true);}
    m_game->removedBullet1(this);
}

void Bullet2::CurrentPos(QPoint pos1)
{
    m_currentPos = pos1;
}

QPoint Bullet2::currentPos() const
{
    return m_currentPos;
}
