

#include "tower.h"
#include "enemy.h"

#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>


const QSize Tower::fixedSize(80, 150);
Tower::Tower(QPoint pos, const QPixmap &sprite)
    :
     m_pos(pos)
    , m_sprite(sprite)
{

}

Tower::~Tower()
{

}



void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::lightGray);
    // 绘制攻击范围
    painter->drawEllipse(m_pos,150,150);


    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);

    painter->translate(m_pos);

    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

