#ifndef TOWER2_H
#define TOWER2_H
#include"tower.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QPoint>
#include <QPixmap>
#include <QObject>
class Tower2  : QObject
{
    Q_OBJECT
public:
    Tower2(QPoint pos, const QPixmap &sprite = QPixmap(":/back/airtrue.png"));
    const QPoint	pos;
    const QPixmap	sprite;
    static const QSize fixedSize;
    void draw(QPainter *painter) const;
};

#endif // TOWER2_H
