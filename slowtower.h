#ifndef SLOWTOWER_H
#define SLOWTOWER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"tower.h"
class slowtower: public Tower
{
public:
    slowtower();
    ~slowtower();
    void levelup();

};

#endif // SLOWTOWER_H
