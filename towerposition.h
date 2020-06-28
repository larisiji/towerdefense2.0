#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H


#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class TowerPosition
{
public:
    TowerPosition(QPoint pos);

    void setHasTower(bool hasTower = true);
    bool hasTower() ;
 QPoint centerPos() ;
    bool containPoint(const QPoint &pos);



private:
    bool		m_hasTower;
    QPoint		m_pos;


    static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
