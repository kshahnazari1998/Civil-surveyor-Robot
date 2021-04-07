#include "Position.h"

Position::Position()
{
    rotatorpos = 0;
    Mn = new Robatmovementmanager();

    laser = new Laser();
    machinevision = new MachineVision();

    Mn->Meu = machinevision;
    triangulation = new Triangulation();
    Sleep(3000);
    int counter = 1;
    ifstream fin("Pagepos.txt");
    while (fin.good())
    {
        fin >> pagex[counter];
        fin >> pagey[counter];
        counter++;
    }
}

void Position::FindMyposition()
{
    boolean pageused[200];
    for (int i = 0; i < 200; i++)
        pageused[i] = false;
    int distopage[10];
    int pagenum[10], counter1 = 0;
    int n = 0;
    int num;
    while (n != 3)
    {

        num = Mn->position;
        while (num == Mn->position)
        {
            int q;
            Mn->RotateTower();
            q = machinevision->DoTheJob();
            if (q == -1)
            {
                Sleep(200);
                q = machinevision->DoTheJob();
            }
            if (q == -1)
            {
                Sleep(200);
                q = machinevision->DoTheJob();
            }
            if (q == -1)
            {
                Sleep(200);
                q = machinevision->DoTheJob();
            }
            cout << "Number detected is = " << q << endl;
            if (q != -1 && pageused[q] == false && q != 0)
            {
                int b = laser->GiveMyDistance();
                if (b == -1)
                {
                    Sleep(1000);
                    int b = laser->GiveMyDistance();
                }
                if (b == -1)
                {
                    Sleep(1000);
                    int b = laser->GiveMyDistance();
                }
                if (b == -1)
                {
                    Sleep(1000);
                    int b = laser->GiveMyDistance();
                }
                if (b != -1)
                {

                    pagenum[counter1] = q;
                    distopage[counter1] = b;
                    counter1++;
                    pageused[q] = true;
                }
            }
        }
        if (counter1 >= 3)
            n = 3;
        else
        {
            Sleep(1000);
            n++;
        }
    }
    if (counter1 >= 3)
    {
        triangulation->calculatepos(pagex[pagenum[0]], pagey[pagenum[0]], pagex[pagenum[1]], pagey[pagenum[1]], pagex[pagenum[2]], pagey[pagenum[2]], distopage[0], distopage[1], distopage[2]);
        x = triangulation->xpos;
        y = triangulation->ypos;
    }
    else
    {
        x = -1;
        y = -1;
    }
}
