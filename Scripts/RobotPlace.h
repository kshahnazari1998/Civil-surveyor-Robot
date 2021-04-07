// Date: 2013
// Created by: Kevin Shahnazari

#ifndef ROBATPLACE_H
#define ROBATPLACE_H

#include "Robatmovementmanager.h"

class RobotPlace
{
public:
    Robatmovementmanager *MM;
    int Direction;
    double RobatDegree;
    int RobatX, RobatY;
    RobotPlace(int x, int y, double degree);
    //if Direction gets 2 means Go Right else if it is 1 means go Left
    double WhatDegree(double yourd, double placed);
    void GotoTheplace(int x, int y);
};

#endif /* ROBATPLACE_H */