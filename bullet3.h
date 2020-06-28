#ifndef BULLET3_H
#define BULLET3_H

#include <QObject>

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include<QPainter>
#include"enemy3.h"
#include"scene2.h"

class QPainter;

class scene2;

class Bullet3 : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet3(QPoint startPos, QPoint targetPoint, int damage, enemy3 *target,
           scene2 *game, int type);

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
 QPixmap	m_sprite;
    QPoint			m_currentPos;
    enemy3 *			m_target;

    scene2 *	m_game;
    int				m_damage;
int m_type;
    static const QSize ms_fixedSize;
};



#endif // BULLET3_H
