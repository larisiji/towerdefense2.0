#include "tower2.h"


#include "tower.h"
#include "enemy.h"

#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower2::fixedSize(80, 150);

Tower2::Tower2(QPoint pos, const QPixmap &sprite)
    :
     pos(pos)
    ,sprite(sprite)
{

}
void Tower2::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::yellow);
    // 绘制攻击范围
    painter->drawEllipse(pos,150,150);


    static const QPoint offsetPoint(-fixedSize.width() / 2, -fixedSize.height() / 2);

    painter->translate(pos);

    painter->drawPixmap(offsetPoint, sprite);
    painter->restore();
}
