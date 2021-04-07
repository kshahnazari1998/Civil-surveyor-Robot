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
