class Triangulation
{
private:
    double xxx, yyy;
    int inline Distancetodot(int x1, int y1, int x2, int y2);

public:
    int xpos, ypos;
    int giveposx();
    int giveposy();
    void calculatepos(int x1, int y1, int x2, int y2, int x3, int y3, int d1, int d2, int d3);
};
