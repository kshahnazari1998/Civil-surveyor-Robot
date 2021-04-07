#include "RobotPlace.h"

RobotPlace::RobotPlace(int x, int y, double degree)
{
    RobatDegree = degree;
    RobatX = x;
    RobatY = y;
    Direction = 0;
}

//if Direction gets 2 means Go Right else if it is 1 means go Left
double RobotPlace::WhatDegree(double yourd, double placed)
{
    if (yourd == placed)
    {
        Direction = 0;
        return 0;
    }
    if (yourd < placed)
    {
        double d1 = yourd + (360 - placed);
        double d2 = placed - yourd;
        if (d1 <= d2)
        {
            Direction = 2;
            return d1;
        }
        else
        {
            Direction = 1;
            return d2;
        }
    }

    if (yourd > placed)
    {
        double d1 = yourd - placed;
        double d2 = (360 - yourd) + placed;
        if (d1 <= d2)
        {
            Direction = 2;
            return d1;
        }
        else
        {
            Direction = 1;
            return d2;
        }
    }
}

void RobotPlace::GotoTheplace(int x, int y)
{
    int X = abs(RobatX - x);
    int Y = abs(RobatY - y);
    double dda = (X * X) + (Y * Y);
    double num1 = sqrt(dda);
    double dis = num1;
    if (x == RobatX && y == RobatY)
        return;
    else if (y == RobatY && x < RobatX)
    {
        double deg = WhatDegree(RobatDegree, 180);
        if (Direction == 2)
            MM->RotateRobotRight(deg);
        else if (Direction == 1)
            MM->RotateRobotLeft(deg);
        MM->moveForward(dis);
    }
    else if (y == RobatY && x > RobatX)
    {
        double deg = WhatDegree(RobatDegree, 0);
        if (Direction == 2)
            MM->RotateRobotRight(deg);
        else if (Direction == 1)
            MM->RotateRobotLeft(deg);
        MM->moveForward(dis);
    }
    else if (x == RobatX && y > RobatY)
    {
        double deg = WhatDegree(RobatDegree, 90);
        if (Direction == 2)
            MM->RotateRobotRight(deg);
        else if (Direction == 1)
            MM->RotateRobotLeft(deg);
        MM->moveForward(dis);
    }
    else if (x == RobatX && y < RobatY)
    {
        double deg = WhatDegree(RobatDegree, 270);
        if (Direction == 2)
            MM->RotateRobotRight(deg);
        else if (Direction == 1)
            MM->RotateRobotLeft(deg);
        MM->moveForward(dis);
    }
    else
    {
        double aa = Y / X;
        double deg1 = atan(aa) * 180 / PI;
        if (x < RobatX && y > RobatY)
            deg1 += 90;
        else if (x < RobatX && y < RobatY)
            deg1 += 180;
        else if (x > RobatX && y < RobatY)
            deg1 += 270;
        double deg = WhatDegree(RobatDegree, deg1);
        if (Direction == 2)
            MM->RotateRobotRight(deg);
        else if (Direction == 1)
            MM->RotateRobotLeft(deg);
        MM->moveForward(dis);
    }
}
