#ifndef ATTACKTOWER_H
#define ATTACKTOWER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"tower.h"

class attacktower: public Tower
{
public:
    attacktower();
    ~attacktower();
    void levelup();
};

#endif // ATTACKTOWER_H
