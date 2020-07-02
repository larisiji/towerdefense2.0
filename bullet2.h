#ifndef BULLET2_H
#define BULLET2_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include<QPainter>
#include"enemy.h"
#include"scene1.h"
#include"enemy2.h"
class QPainter;
class enemy;
class scene1;

class Bullet2 : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet2(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
           scene1 *game, const QPixmap &sprite = QPixmap(":/back/bullet6.png"));
    Bullet2(QPoint startPos, QPoint targetPoint, int damage, enemy2 *target,
           scene1 *game, const QPixmap &sprite = QPixmap(":/back/bullet6.png"));
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos1);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
   QPixmap	m_sprite;
    QPoint			m_currentPos;
    enemy *			m_target;
    scene1 *	m_game;
    enemy2*         m_target2;
    int				m_damage;

    static const QSize fixedSize;
};
#endif // BULLET2_H
