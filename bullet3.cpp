#include "bullet3.h"


#include "enemy.h"
#include "scene2.h"
#include <QPainter>
#include <QPropertyAnimation>
#include"enemy2.h"
const QSize Bullet3::ms_fixedSize(8, 8);

Bullet3::Bullet3(QPoint startPos, QPoint targetPoint, int damage, enemy3 *target,
               scene2 *game,int type)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
    ,m_type(type)
{
    if(m_type==1)
        m_sprite=QPixmap(":/back/bullet6.png");
    if(m_type==2)
    m_sprite=QPixmap(":/back/bullet2.png");
}

void Bullet3::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet3::move()
{

    static const int duration = 500;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}

void Bullet3::hitTarget()
{
  if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(m_damage,true);

    m_game->removedBullet(this);
}

void Bullet3::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

QPoint Bullet3::currentPos() const
{
    return m_currentPos;
}
