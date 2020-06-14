#ifndef TOWER_H
#define TOWER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;

class MainWindow;
class QTimer;

class Tower : QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, const QPixmap &sprite = QPixmap(":/back/jjj4.png"));
    ~Tower();

    void draw(QPainter *painter) const;

 static const QSize fixedSize;





    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
