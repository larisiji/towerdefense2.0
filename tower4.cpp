#include "tower4.h"
#include"bullet3.h"
#include"collision.h"
#include"enemy3.h"
#include<QSound>
const QSize Tower4::fixedSize(130, 130);
Tower4::Tower4(QPoint pos, scene2*game,int type):
    m_pos(pos),
    m_type(type),
    m_game(game),
    m_level(0),
    m_attacking(false)
    , m_attackRange(220)
    , m_fireRate(1000)

      , m_chooseEnemy(NULL)
{

    if(type==1)
     {  m_damage=30;
        m_sprite= QPixmap(":back/zhangyu.png");
    }
   if(type==2)
 {
       m_damage=20;
       m_sprite=QPixmap(":back/sun.png");}

   m_fireRateTimer = new QTimer(this);
   connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shoot()));

}
Tower4::~Tower4()
{

    delete m_fireRateTimer;
    m_fireRateTimer = NULL;

}
void Tower4::levelup(){
    m_fireRate+=100;
    m_level+=1;
    m_attackRange+=10;
    m_damage+=10;

}
int Tower4::level(){
    return m_level;
}
void Tower4::shoot()
{

    if(m_type==1)
   {
        Bullet3 *bullet = new Bullet3(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,1);
    bullet->move();
    m_game->addBullet(bullet);


}
    if(m_type==2)
    {
        Bullet3 *bullet = new Bullet3(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,2);
            bullet->move();
            m_game->addBullet(bullet);

    }
}
void Tower4::checkEnemyInRange()
{

        if (m_chooseEnemy)
    {


        if (!collision(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {

        QList<enemy3 *> enemyList = m_game->enemyList();
        foreach (enemy3 *Enemy, enemyList)
        {
            if (collision(m_pos, m_attackRange, Enemy->pos(), 1))
            {
                chooseEnemyForAttack(Enemy);
                break;
            }
        }
        }
   }

void Tower4::draw(QPainter *painter) const
{
    painter->save();
    if(m_type==2)
    painter->setPen(Qt::red);

    if(m_type==1)
            painter->setPen(Qt::blue);
    painter->drawEllipse(m_pos,m_attackRange,m_attackRange);


    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);

    painter->translate(m_pos);

    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
void Tower4::attackEnemy()
{

    m_fireRateTimer->start(m_fireRate);

}
void Tower4::chooseEnemyForAttack(enemy3 *Enemy)
{

    m_chooseEnemy = Enemy;

    attackEnemy();

    m_chooseEnemy->getAttacked(this);
}
void Tower4::targetKilled()
{


    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();


}
void Tower4::lostSightOfEnemy()
{

    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();


}
bool Tower4::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + fixedSize.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + fixedSize.height());
    return isXInHere && isYInHere;
}
bool Tower4::hasEnemy()
{
    if(m_chooseEnemy)
        return true;
    else {
        return false;
    }
}
