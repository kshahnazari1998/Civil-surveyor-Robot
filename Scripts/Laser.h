// Date: 2013
// Created by: Kevin Shahnazari

#ifndef LASER_H
#define LASER_H

#include <highgui.h>
#include <cxcore.h>
#include <windows.h>

class Laser
{
private:
    HANDLE hComm;

public:
    Laser();
    int GiveMyDistance();
};

#endif /* LASER_H */