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