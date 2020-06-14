#ifndef ENEMY_H
#define ENEMY_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class enemy : public QObject
{
    Q_OBJECT
public:
    enemy(WayPoint *startWayPoint, const QPixmap &sprite = QPixmap(":/back/enemy1.png"));
    ~enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
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

    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};



#endif // ENEMY_H
