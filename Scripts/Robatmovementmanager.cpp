
#include "Robatmovementmanager.h"

void Robatmovementmanager::moveForward(double dis)
{
    con->resetmotorencoders();
    countercharkh = 0;
    con->MoveForwardOn();
    while (countercharkh <= dis * 8.6)
    {
        int encod = con->rightsideencoder();
        countercharkh += encod;

        con->resetmotorencoders();
    }
    con->MoveForwardOff();
    Sleep(2000);
}

Robatmovementmanager::Robatmovementmanager()
{
    con = new ContactWithRobot;
    con->resetTowerencoder();
    position = 0;
    counterborj = 0;
    countercharkh = 0;
}

void Robatmovementmanager::moveBackward(double dis)
{
    con->resetmotorencoders();
    countercharkh = 0;
    con->MoveBackwardOn();
    while (countercharkh <= dis * 9.7)
    {
        int encod = con->rightsideencoder();
        countercharkh -= encod;
        con->resetmotorencoders();
    }
    con->MoveBackwardOff();
    Sleep(2000);
}

void Robatmovementmanager::RotateRobotRight(int degree)
{
    con->RotateRightOn();
    con->resetmotorencoders();
    countercharkh = 0;
    int encod = 0;
    while (countercharkh <= degree * 5.5)
    {
        encod = con->leftsideencoder();
        countercharkh -= encod;
        con->resetmotorencoders();
        //	cout<<countercharkh<<endl;
    }
    con->RotateRightOff();
    Sleep(2000);
}

void Robatmovementmanager::RotateRobotLeft(int degree)
{
    con->RotateLeftOn();
    con->resetmotorencoders();
    countercharkh = 0;
    int encod = 0;

    while (countercharkh <= degree * 2.6)
    {
        encod = con->rightsideencoder();
        countercharkh += encod;

        con->resetmotorencoders();
    }
    con->RotateLeftOff();
    Sleep(2000);
}

void Robatmovementmanager::RotateTower()
{
    if (position == 0)
    {
        int ssee;
        ssee = Meu->seeIfThereIsRed();
        if (ssee == 1)
        {
            con->TowerClockwiseOn();
            con->TowerClockwiseOff();
            int encod = con->toptowerencoder();
            counterborj -= encod;
            con->resetTowerencoder();
            //cout<<counterborj<<endl;
            if (counterborj >= 2200)
            {
                counterborj = 0;
                position = 1;
                encod = 0;
            }
        }
        if (ssee == 0)
        {
            int encod;
            con->TowerClockwiseOn();
            while (ssee == 0 && counterborj <= 2200)
            {
                //cout<<counterborj<<endl;
                encod = con->toptowerencoder();
                counterborj -= encod;
                con->resetTowerencoder();
                ssee = Meu->seeIfThereIsRed();
            }
            con->TowerClockwiseOff();
            encod = con->toptowerencoder();
            counterborj -= encod;
            con->resetTowerencoder();
            if (counterborj >= 2200)
            {
                counterborj = 0;
                position = 1;
                encod = 0;
            }
        }
    }
    else
    {
        int ssee;
        ssee = Meu->seeIfThereIsRed();
        if (ssee == 1)
        {
            con->TowerAntiClockwiseOn();
            con->TowerAntiClockwiseOff();
            int encod = con->toptowerencoder();
            counterborj += encod;
            con->resetTowerencoder();
            //cout<<counterborj<<endl;
            if (counterborj >= 2200)
            {
                counterborj = 0;
                position = 0;
                encod = 0;
            }
        }
        if (ssee == 0)
        {
            int tt = 0;
            int encod;
            con->TowerAntiClockwiseOn();
            while (ssee == 0 && counterborj <= 2200)
            {
                tt += 1;
                if (tt > 3)
                {
                    tt = 0;
                    encod = con->toptowerencoder();
                    counterborj += encod;
                    con->resetTowerencoder();
                    //		cout<<counterborj<<endl;
                }
                ssee = Meu->seeIfThereIsRed();
            }
            encod = con->toptowerencoder();
            counterborj += encod;
            con->resetTowerencoder();
            con->TowerAntiClockwiseOff();
            if (counterborj >= 2200)
            {
                counterborj = 0;
                position = 0;
                encod = 0;
            }
        }
    }
}

void Robatmovementmanager::TurnonThebrush()
{
    con->TurnOnBrush();
}

void Robatmovementmanager::Turnoffthebrush()
{
    con->TurnoffBrush();
}
