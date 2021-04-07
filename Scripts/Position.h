// Date: 2013
// Created by: Kevin Shahnazari

#ifndef POSITION_H
#define POSITION_H

#include "MachineVision.h"
#include "Triangulation.h"
#include "Laser.h"

class Position
{
    int rotatorpos;
    Triangulation *triangulation;
    MachineVision *machinevision;
    Laser *laser;
    int pagex[70], pagey[70];

public:
    Robatmovementmanager *Mn;
    int x, y;
    Position();
    void FindMyposition();
};

#endif /* POSITION_H */