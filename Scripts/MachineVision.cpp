#include <cv.h>
#include "MachineVision.h"
#include <cxcore.h>
#include <highgui.h>
#include <cmath>
#include <windows.h>

using namespace std;

#define ImageRange 20
#define RedExistRange 50
#define Colorlenght 10

#define PI 3.14159265359

MachineVision::MachineVision()
{
    capture = 0;
    capture = cvCaptureFromCAM(-1);
    max1 = 0;
    maxest = 0;
}

int MachineVision::CheckMiddle()
{
    if (maxest < 1)
        return 0;
    else
        return 1;
    /*int mid = img->width/2;
		for (int i=mid-deghat;i<=mid+deghat;i++)
		for (int j=0;j<img->height;j++)
		{
		int pix = (int) CV_IMAGE_ELEM(bin,uchar,j,i);
		if (pix==255) return 1;
		}*/

    return 0;
}

void MachineVision::helpbig(int y, int x)
{

    int q;
    q = (int)CV_IMAGE_ELEM(bin, uchar, y, x);
    if (q == 0)
        a[y][x] = -1;
    if (q == 255 && a[y][x] != 1 && a[y][x] != 2)
    {
        max1 += 1;
        a[y][x] = 1;
        if (y != 0)
        {
            if (a[y - 1][x] == 0)
                helpbig(y - 1, x);
        }
        if (y != bin->height - 1)
        {
            if (a[y + 1][x] == 0)
                helpbig(y + 1, x);
        }
        if (x != bin->width - 1)
        {
            if (a[y][x + 1] == 0)
                helpbig(y, x + 1);
        }
        if (x != 0)
        {
            if (a[y][x - 1] == 0)
                helpbig(y, x - 1);
        }
    }
}

void MachineVision::extractbigpart()
{
    int q;
    a = new int *[bin->height];
    for (int i = 0; i < bin->height; i++)
        a[i] = new int[bin->width];
    for (int i = 0; i < bin->height; i++)
        for (int j = 0; j < bin->width; j++)
            a[i][j] = 0;

    for (int i = 0; i < bin->height; i++)
        for (int j = 0; j < bin->width; j++)
        {
            if (a[i][j] == 0)
            {
                q = (int)CV_IMAGE_ELEM(bin, uchar, i, j);
                if (q == 0)
                    a[i][j] = -1;
                if (q == 255)
                {
                    max1 = 0;
                    helpbig(i, j);
                    if (max1 > maxest)
                    {
                        maxest = max1;
                        for (int ii = 0; ii < bin->height; ii++)
                            for (int jj = 0; jj < bin->width; jj++)
                            {
                                if (a[ii][jj] == 2)
                                {
                                    a[ii][jj] = -1;
                                    CV_IMAGE_ELEM(bin, uchar, ii, jj) = 0;
                                }
                                if (a[ii][jj] == 1)
                                    a[ii][jj] = 2;
                            }
                    }
                    else
                    {
                        for (int ii = 0; ii < bin->height; ii++)
                            for (int jj = 0; jj < bin->width; jj++)
                            {
                                if (a[ii][jj] == 1)
                                {
                                    a[ii][jj] = -1;
                                    CV_IMAGE_ELEM(bin, uchar, ii, jj) = 0;
                                }
                            }
                    }
                }
            }
        }
    for (int i = 0; i < bin->height; i++)
        delete[] a[i];
    delete a;
}

void MachineVision::getAverageCenter()
{
    int lastnumber;
    long long int Nums = 0, xNums = 0;
    int counter = 0;
    for (int i = 0; i < bin->height; i++)
        for (int j = 0; j < bin->width; j++)
        {
            int q;
            q = (int)CV_IMAGE_ELEM(bin, uchar, i, j);
            if (q == 255)
            {
                xNums += j;
                Nums += i;
                counter++;
            }
        }
    lastnumber = Nums / counter;
    midy = lastnumber;
    lastnumber = xNums / counter;
    midx = lastnumber;
}

int MachineVision::DoThething()
{
    a = 0;
    finalnum = 0;
    max1 = 0;
    maxest = 0;
    midx = 0;
    midy = 0;
    int camerror = 0;
    //img2 = cvLoadImage("testImage6.jpg");
    camerror = takeimage();
    //if (camerror==1)
    //return -2;
    //if (camerror==2)
    //return -3;
    //Image Show
    //cvShowImage("display",img2);
    //int c = cvWaitKey(2000);
    img = cvCreateImage(cvSize(img2->width, img2->height), IPL_DEPTH_8U, 3);

    cvCvtColor(img2, img, CV_BGR2HSV);

    bin = cvCreateImage(cvSize(ImageRange * 2 + 1, img->height), 8, 1);
    cvZero(bin);
    int qqq = (img->width / 2);
    for (int i = 10; i < img->height - 10; i++)
    {
        uchar *data = (uchar *)(img2->imageData + i * img2->widthStep);
        for (int j = qqq - ImageRange; j <= qqq + ImageRange; j++)
        {

            int v = ((uchar *)(img->imageData + i * img->widthStep))[j * img->nChannels + 2];
            int s = ((uchar *)(img->imageData + i * img->widthStep))[j * img->nChannels + 1];
            int h = ((uchar *)(img->imageData + i * img->widthStep))[j * img->nChannels + 0];
            if ((h >= 0 && h <= 15) || (h >= 165 && h <= 180))
            {
                if ((s > 50) && (v > 50))
                {
                    CV_IMAGE_ELEM(bin, uchar, i, j - qqq - ImageRange) = 255;
                    data[j * 3 + 0] = 0;
                    data[j * 3 + 1] = 0;
                    data[j * 3 + 2] = 0;
                }
                else
                {
                    CV_IMAGE_ELEM(bin, uchar, i, j - qqq - ImageRange) = 0;
                }
            }
            else
                CV_IMAGE_ELEM(bin, uchar, i, j - qqq - ImageRange) = 0;
        }
    }
    //Image Show and cvwaitkey!
    //cvShowImage("Red Detected!", img2);
    //int c = cvWaitKey(2000);
    cvErode(bin, bin, NULL, 4);
    cvDilate(bin, bin, NULL, 4);
    extractbigpart();
    //Image and cvwait key
    //cvShowImage("display1", bin);
    //int c = cvWaitKey(2000);
    int y = CheckMiddle();

    if (y == 0)
    {
        return 0;

        //release image
        cvReleaseImage(&img);
        cvReleaseImage(&bin);
        //	cvReleaseImage(&img2);
    }
    else if (y == 1)
    {
        getAverageCenter();
        CV_IMAGE_ELEM(bin, uchar, midy, midx) = 0;
        int lastcolor = 1, checkthelastcolor = 0, checkpointcolor = 0;
        boolean gogo = true;
        int breaknum = 0;
        int colorcon = 3;
        int numberx = qqq - ImageRange + midx;
        int numbercolor[6];
        for (int i = 0; i < 6; i++)
            numbercolor[i] = 0;
        int midyrem = midy;
        while (gogo)
        {
            if (midy == 480)
                return -1;
            midy++;
            int v = ((uchar *)(img->imageData + midy * img->widthStep))[numberx * img->nChannels + 2];
            int s = ((uchar *)(img->imageData + midy * img->widthStep))[numberx * img->nChannels + 1];
            int h = ((uchar *)(img->imageData + midy * img->widthStep))[numberx * img->nChannels + 0];
            if ((s > 60) && (v > 60))
            {
                breaknum = 0;
                if ((h >= 0 && h <= 30) || (h >= 150 && h <= 180))
                {
                    if (lastcolor != 1)
                    {
                        if (checkpointcolor != 1)
                            checkthelastcolor = 0;
                        checkpointcolor = 1;
                        checkthelastcolor++;
                    }
                }
                else if ((h >= 120 && h <= 150) || (h <= 120 && h >= 90))
                {
                    if (lastcolor != 2)
                    {
                        if (checkpointcolor != 2)
                            checkthelastcolor = 0;
                        checkpointcolor = 2;
                        checkthelastcolor++;
                    }
                }
                else if ((h >= 60 && h <= 90) || (h <= 60 && h >= 30))
                {
                    if (lastcolor != 3)
                    {
                        if (checkpointcolor != 3)
                            checkthelastcolor = 0;
                        checkpointcolor = 3;
                        checkthelastcolor++;
                    }
                }
            }
            else
            {
                breaknum++;
            }
            if (breaknum == Colorlenght)
                break;
            if (checkthelastcolor >= 5 && numbercolor[colorcon - 1] != checkpointcolor)
            {
                lastcolor = checkpointcolor;
                checkthelastcolor = 0;
                numbercolor[colorcon] = checkpointcolor;
                colorcon++;
            }
            if (colorcon == 6)
                gogo = false;
        }
        if (breaknum == Colorlenght)
        {
            cvReleaseImage(&img);
            cvReleaseImage(&bin);
            return -1;
        }
        lastcolor = 1;
        checkthelastcolor = 0;
        checkpointcolor = 0;
        gogo = true;
        colorcon = 2;
        breaknum = 0;
        numberx = qqq - ImageRange + midx;
        midy = midyrem;
        while (gogo)
        {
            if (midy == 0)
                return -1;
            midy--;
            int v = ((uchar *)(img->imageData + midy * img->widthStep))[numberx * img->nChannels + 2];
            int s = ((uchar *)(img->imageData + midy * img->widthStep))[numberx * img->nChannels + 1];
            int h = ((uchar *)(img->imageData + midy * img->widthStep))[numberx * img->nChannels + 0];
            if ((s > 60) && (v > 60))
            {
                if ((h >= 0 && h <= 30) || (h >= 150 && h <= 180))
                {
                    if (lastcolor != 1)
                    {
                        if (checkpointcolor != 1)
                            checkthelastcolor = 0;
                        checkpointcolor = 1;
                        checkthelastcolor++;
                    }
                }
                else if ((h >= 120 && h <= 150) || (h <= 120 && h >= 90))
                {
                    if (lastcolor != 2)
                    {
                        if (checkpointcolor != 2)
                            checkthelastcolor = 0;
                        checkpointcolor = 2;
                        checkthelastcolor++;
                    }
                }
                else if ((h >= 60 && h <= 90) || (h <= 60 && h >= 30))
                {
                    if (lastcolor != 3)
                    {
                        if (checkpointcolor != 3)
                            checkthelastcolor = 0;
                        checkpointcolor = 3;
                        checkthelastcolor++;
                    }
                }
            }
            else
            {
                breaknum++;
            }
            if (breaknum == Colorlenght)
                break;
            if (checkthelastcolor >= 5 && numbercolor[colorcon - 1] != checkpointcolor)
            {
                lastcolor = checkpointcolor;
                checkthelastcolor = 0;
                numbercolor[colorcon] = checkpointcolor;
                colorcon--;
            }
            if (colorcon == -1)
                gogo = false;
        }
        if (breaknum == Colorlenght)
        {
            cvReleaseImage(&img);
            cvReleaseImage(&bin);
            return -1;
        }
        for (int i = 0; i < 6; i++)
            numbercolor[i]--;
        if (numbercolor[2] == 2)
            numbercolor[2] = 0;
        if (numbercolor[3] == 2)
            numbercolor[3] = 0;
        for (int i = 0; i < 2; i++)
            if (numbercolor[i] == 2)
                numbercolor[i] = numbercolor[i + 1];
        for (int i = 4; i < 6; i++)
            if (numbercolor[i] == 2)
                numbercolor[i] = numbercolor[i - 1];
        int tavan = 1;
        int finalnumber = 0;
        for (int i = 0; i <= 5; i++)
        {
            finalnumber += tavan * numbercolor[i];
            tavan *= 2;
        }
        finalnum = finalnumber;

        //release image
        cvReleaseImage(&img);
        cvReleaseImage(&bin);
        //	cvReleaseImage(&img2);
        return finalnum;
    }

    cvShowImage("display", bin);
    cvCvtColor(img, img, CV_HSV2BGR);
}

int MachineVision::seeIfThereIsRed()
{
    a = 0;
    finalnum = 0;
    max1 = 0;
    maxest = 0;
    midx = 0;
    midy = 0;
    int camerror = 0;
    //img2 = cvLoadImage("testImage6.jpg");
    camerror = takeimage();
    //if (camerror==1)
    //return -2;
    //if (camerror==2)
    //return -3;
    //Image Show
    //cvShowImage("display",img2);
    //int c = cvWaitKey(2000);
    img = cvCreateImage(cvSize(img2->width, img2->height), IPL_DEPTH_8U, 3);

    cvCvtColor(img2, img, CV_BGR2HSV);

    bin = cvCreateImage(cvSize(RedExistRange * 2 + 1, img->height), 8, 1);
    cvZero(bin);
    int qqq = (img->width / 2);
    for (int i = 10; i < img->height - 10; i++)
    {
        uchar *data = (uchar *)(img2->imageData + i * img2->widthStep);
        for (int j = qqq - RedExistRange; j <= qqq + RedExistRange; j++)
        {

            int v = ((uchar *)(img->imageData + i * img->widthStep))[j * img->nChannels + 2];
            int s = ((uchar *)(img->imageData + i * img->widthStep))[j * img->nChannels + 1];
            int h = ((uchar *)(img->imageData + i * img->widthStep))[j * img->nChannels + 0];
            if ((h >= 0 && h <= 15) || (h >= 165 && h <= 180))
            {
                if ((s > 50) && (v > 50))
                {
                    CV_IMAGE_ELEM(bin, uchar, i, j - qqq - ImageRange) = 255;
                    data[j * 3 + 0] = 0;
                    data[j * 3 + 1] = 0;
                    data[j * 3 + 2] = 0;
                }
                else
                {
                    CV_IMAGE_ELEM(bin, uchar, i, j - qqq - RedExistRange) = 0;
                }
            }
            else
                CV_IMAGE_ELEM(bin, uchar, i, j - qqq - RedExistRange) = 0;
        }
    }
    //Image Show and cvwaitkey!
    //cvShowImage("Red Detected!", img2);
    //int c = cvWaitKey(2000);
    cvErode(bin, bin, NULL, 4);
    cvDilate(bin, bin, NULL, 4);
    extractbigpart();
    //Image and cvwait key
    //cvShowImage("display1", bin);
    //int c = cvWaitKey(2000);
    int y = CheckMiddle();

    //release image
    cvReleaseImage(&img);
    cvReleaseImage(&bin);
    //img2 = 0;
    //cvReleaseImage(&img2);

    if (y == 0)
    {
        return 0;
    }
    else
        return 1;
}

int MachineVision::takeimage()
{
    if (!capture)
        return 1;
    //img2 = 0;
    img2 = cvQueryFrame(capture);

    if (!img2)
        return 2;
    return 0;
}

int MachineVision::DoTheJob()
{
    int ffff = DoThething();
    return ffff;
}
