#include <cmath>
#include "Triangulation.h"

int inline Triangulation::Distancetodot(int x1, int y1, int x2, int y2)
{

    xxx = x2 - x1;
    yyy = y2 - y1;
    xxx = xxx * xxx;
    yyy = yyy * yyy;
    int jazr = sqrt(xxx + yyy);
    return jazr;
}

int Triangulation::giveposx()
{
    return xpos;
}
int Triangulation::giveposy()
{
    return ypos;
}
void Triangulation::calculatepos(int x1, int y1, int x2, int y2, int x3, int y3, int d1, int d2, int d3)
{
    int mostx = max(x1, x2);
    mostx = max(mostx, x3);
    int mosty = max(y1, y2);
    mosty = max(mosty, y3);
    int lowx = min(x1, x2);
    lowx = min(lowx, x3);
    int lowy = min(y1, y2);
    lowy = min(lowy, y3);
    double minD = 99999999;
    int x, y;
    double td;
    for (int i = lowx; i <= mostx; i++)
        for (int j = lowy; j <= mosty; j++)
        {
            td = abs(d1 - Distancetodot(x1, y1, i, j));
            td += abs(d2 - Distancetodot(x2, y2, i, j));
            td += abs(d3 - Distancetodot(x3, y3, i, j));
            if (td < minD)
            {
                minD = td;
                xpos = i;
                ypos = j;
            }
        }
}
