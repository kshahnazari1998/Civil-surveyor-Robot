// Date: 2013
// Created by: Kevin Shahnazari

#ifndef ROBATMOVEMENTMANAGER_H
#define ROBATMOVEMENTMANAGER_H

#include "ContactWithRobot.h"
#include "MachineVision.h"

class Robatmovementmanager
{
public:
    ContactWithRobot *con;
    MachineVision *Meu;
    int position;
    int counterborj;
    long long int countercharkh;
    Robatmovementmanager();
    void moveForward(double dis);
    void moveBackward(double dis);
    void RotateRobotRight(int degree);
    void RotateRobotLeft(int degree);
    void RotateTower();
    void TurnonThebrush();
    void Turnoffthebrush();
};

#endif /* ROBATMOVEMENTMANAGER_H */