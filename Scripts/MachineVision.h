#include <cv.h>

class MachineVision
{

private:
    int finalnum;
    int max1, maxest;
    IplImage *img;
    IplImage *bin;
    int **a;
    int midx, midy;
    CvCapture *capture;
    IplImage *img2;
    int CheckMiddle();
    void helpbig(int y, int x);
    void extractbigpart();
    void getAverageCenter();

public:
    MachineVision();
    int DoThething();
    int seeIfThereIsRed();
    int takeimage();
    int DoTheJob();
};