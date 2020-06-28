#ifndef ENEMY3_H
#define ENEMY3_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
class WayPoint;
class QPainter;

class scene2;
class Tower4;
class enemy3 : public QObject
{
    Q_OBJECT
public:
    enemy3(WayPoint *startWayPoint, scene2*game,int type);
    ~enemy3();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage,bool speed);
    void getRemoved();
    void getAttacked(Tower4 *attacker);

    void gotLostSight(Tower4 *attacker);

    QPoint pos() const;

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
    scene2 *	m_game;
    QList<Tower4 *>	m_attackedTowersList;
int m_type;
 QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};

#endif // ENEMY3_H
