
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "ContactWithRobot.h"
#include "MachineVision.h"
#include "Robatmovementmanager.h"
#include "Triangulation.h"
#include "Laser.h"
#include "RobotPlace.h"
#include "Position.h"

using namespace std;

#define ImageRange 20
#define RedExistRange 50
#define Colorlenght 10

#define PI 3.14159265359

class Finisherclass
{
	Position *position;
	Robatmovementmanager *robatmovementmanager;
	RobotPlace *robatplace;
	int placestogox[500], placestogoy[500];
	int targetx, targety;
	int x, y;

public:
	Finisherclass(int degree)
	{
		for (int i = 0; i < 500; i++)
		{
			placestogox[i] = -1;
			placestogoy[i] = -1;
		}
		position = new Position;
		position->FindMyposition();
		int x = position->x;
		int y = position->y;
		robatplace = new RobotPlace(x, y, degree);
		robatplace->MM = position->Mn;
		robatmovementmanager = position->Mn;
		ifstream fin("Targetpos.txt");
		int counter = 0;
		while (fin.good())
		{
			fin >> placestogox[counter];
			fin >> placestogoy[counter];
			counter++;
		}
	}

	void DrawThem()
	{
		int n = 0;
		while (n == 0)
		{
			int mindis = 10000000, j;
			for (int i = 0; i < 500; i++)
			{
				if (placestogox[i] != -1)
				{
					double dis = ((y - placestogoy[i]) * (y - placestogoy[i])) + ((x - placestogox[i]) * (x - placestogox[i]));
					dis = sqrt(dis);
					if (dis < mindis)
					{
						targetx = placestogox[i];
						targety = placestogoy[i];
						mindis = dis;
						j = i;
						break;
					}
				}
			}
			placestogox[j] = -1;
			placestogoy[j] = -1;

			int q = 0;
			while (q == 0)
			{
				robatplace->GotoTheplace(targetx, targety);
				position->FindMyposition();
				int x1, y1, deg;
				x1 = position->x;
				y1 = position->y;
				robatplace->RobatX = x1;
				robatplace->RobatY = y1;
				int xx, yy;
				xx = abs(x - x1);
				yy = abs(y - y1);

				if (x1 == x && y1 < y)
				{
					robatplace->RobatDegree = 270;
				}
				else if (x1 == x && y1 > y)
				{
					robatplace->RobatDegree = 90;
				}
				else if (y1 == y && x1 > x)
				{
					robatplace->RobatDegree = 0;
				}
				else if (y1 == y && x1 < x)
				{
					robatplace->RobatDegree = 180;
				}
				else
				{
					double aa = yy / xx;
					int deg = atan(aa) * 180 / PI;
					if (x1 < x && y1 > y)
						deg += 90;
					else if (x1 < x && y1 < y)
						deg += 180;
					else if (x1 > x && y1 < y)
						deg += 270;
					robatplace->RobatDegree = deg;
				}
				y = y1;
				x = x1;
				double dis = ((targety - y) * (targety - y)) + ((targetx - x) * (targetx - x));
				int dis1 = dis;
				if (dis1 < 100)
				{
					robatmovementmanager->TurnonThebrush();
					Sleep(1000);
					robatmovementmanager->Turnoffthebrush();
					q = 1;
				}
			}
			boolean change = true;
			for (int i = 0; i < 500; i++)
			{
				if (placestogox[i] != -1)
					change = false;
			}
			if (change == true)
				n = 1;
		}
	}
};

int main()
{
	Finisherclass ff(0);
	ff.DrawThem();
}
