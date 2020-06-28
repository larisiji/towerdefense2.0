#ifndef ENEMY_H
#define ENEMY_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
class WayPoint;
class QPainter;
class Tower2;
class Tower;
class scene1;
class Tower3;
class enemy : public QObject
{
    Q_OBJECT
public:
    enemy(WayPoint *startWayPoint, scene1*game,const QPixmap &sprite = QPixmap(":/back/enemy1.png"));
    ~enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage,bool speed);
    void getRemoved();
    void getAttacked(Tower *attacker);
     void getAttacked(Tower3 *attacker2);
    void gotLostSight(Tower *attacker);
    void gotLostSight(Tower3 *attacker2);
    void getAttacked1(Tower2 *attacker1);
    void gotLostSight1(Tower2 *attacker1);
    QPoint pos() const;
   void accelerate();
public slots:
    void doActivate();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
 qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    scene1 *	m_game;
    QList<Tower *>	m_attackedTowersList;
    QList<Tower2*>  m_attackedTowersList2;
QList<Tower3*>       m_attackedTowersList3;
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};



#endif // ENEMY_H
