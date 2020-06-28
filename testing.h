#ifndef TESTING_H
#define TESTING_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"enemy2.h"
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include<QPainter>
#include"enemy.h"
#include"scene1.h"

class QPainter;
class enemy;
class scene1;

class bullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
           scene1 *game, const QPixmap &sprite = QPixmap(":/back/bullet2.png"));
    bullet(QPoint startPos, QPoint targetPoint, int damage, enemy2 *target,
           scene1 *game, const QPixmap &sprite = QPixmap(":/back/bullet2.png"));
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    enemy *			m_target;
    enemy2*         m_target2;
    scene1 *	m_game;
    int				m_damage;

    static const QSize ms_fixedSize;
};

#endif // TESTING_H
