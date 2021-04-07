#include <highgui.h>
#include <cxcore.h>
#include <windows.h>

Laser::Laser()
{

    hComm = CreateFileW(
        L"Com6",
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
}

int Laser::GiveMyDistance()
{
    int lastnumber = 0;
    bool rightornot = true;
    string all = "s0g\r\n";
    DWORD dwNumberOfBytesWritten;
    WriteFile(hComm, all.c_str(), 5, &dwNumberOfBytesWritten, NULL);
    Sleep(2000);
    unsigned char readeddata[16];
    ReadFile(hComm, &readeddata, 16, &dwNumberOfBytesWritten, NULL);
    string testoutput = "";
    for (int i = 4; i < 12; i++)
    {
        if (readeddata[i] >= 48 && readeddata[i] <= 57)
            ;
        else
            rightornot = false;
        testoutput += readeddata[i];
    }
    if (rightornot == false)
    {
        //		reset();
        return -1; //error
    }
    else
    {
        testoutput.erase(6, 2);
        for (int i = 0; i < 6; i++)
        {
            lastnumber *= 10;
            lastnumber += testoutput[i] - 48;
        }
        return lastnumber;
    }
}
