#include "pch.h"
#include "ZoneAndSightCalculator.h"
#include <iostream>
#include <TypeZoneLaunch.h>

using namespace tw;

ZoneAndSightCalculator * ZoneAndSightCalculator::instance = NULL;

ZoneAndSightCalculator::ZoneAndSightCalculator()
{
}


ZoneAndSightCalculator::~ZoneAndSightCalculator()
{
}

ZoneAndSightCalculator * ZoneAndSightCalculator::getInstance()
{
	if (instance == NULL)
		instance = new ZoneAndSightCalculator();

	return instance;
}


std::vector<Point2D> ZoneAndSightCalculator::generateZone(int x, int y, int minPO, int maxPO, TypeZoneLaunch type)
{
	std::vector<Point2D> targettableCells;
	int i;

	if (type == TypeZoneLaunch::LINE){

		for (i = x+minPO+1; i <= x + minPO + maxPO; i++) {
			targettableCells.push_back(Point2D(i, y));
		}
		for (i = x-minPO-1; i >= x - minPO - maxPO; i--) {
			targettableCells.push_back(Point2D(i, y));
		}
		for (i = y+minPO+1; i <= y + minPO + maxPO; i++) {
			targettableCells.push_back(Point2D(x, i));
		}
		for (i = y-minPO-1; i >= y - minPO -maxPO; i--) {
			targettableCells.push_back(Point2D(x, i));
		}
	}

	if (type == TypeZoneLaunch::DIAGONAL) {
		int x1 = x;
		int y1 = y;
		for (i = 0; i <= maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 + 1;
			y1 = y1 + 1;
		}
		x1 = x;
		y1 = y;
		for (i = 0; i <= maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 - 1;
			y1 = y1 - 1;

		}
		x1 = x;
		y1 = y;
		for (i = 0; i <= maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 + 1;
			y1 = y1 - 1;

		}
		x1 = x;
		y1 = y;
		for (i = 0; i <= maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 - 1;
			y1 = y1 + 1;

		}
	}

	if (type == TypeZoneLaunch::STAR) {
		/*int x1, y1;

		for (i = x; i <= x + 2; i++) {
			targettableCells.push_back(Point2D(i, y));
		}
		for (i = x; i >= x - 2; i--) {
			targettableCells.push_back(Point2D(i, y));
		}
		for (i = y; i <= y + 2; i++) {
			targettableCells.push_back(Point2D(x, i));
		}
		for (i = y; i >= y - 2; i--) {
			targettableCells.push_back(Point2D(x, i));
		}

		for (i = 0; i <= 1; i++) {
			targettableCells.push_back(Point2D(x, y));

			x1 = x + 1;
			y1 = y + 1;
			targettableCells.push_back(Point2D(x1, y1));

			x1 = x - 1;
			y1 = y - 1;
			targettableCells.push_back(Point2D(x1, y1));

			x1 = x + 1;
			y1 = y - 1;
			targettableCells.push_back(Point2D(x1, y1));

			x1 = x - 1;
			y1 = y + 1;
			targettableCells.push_back(Point2D(x1, y1));

		for (i = x-maxPO; i < x + maxPO; i++) {
			for (int j = y-maxPO; j < y + maxPO; j++) {
				targettableCells.push_back(Point2D(i,j));
			}
		}
		int i = x + maxPO;
		for (int j = y - maxPO; j < y + maxPO; j++) {
			targettableCells.push_back(Point2D(i, j));
		}
		i = x - maxPO;
		for (int j = y - maxPO; j < y + maxPO; j++) {
			targettableCells.push_back(Point2D(i, j));
		}
		int j = y + maxPO;
		for (i = x - maxPO; i < x + maxPO; i++) {
			targettableCells.push_back(Point2D(i, j));
		}
		j = y - maxPO;
		for (i = x - maxPO; i < x + maxPO; i++) {
			targettableCells.push_back(Point2D(i, j));
		}*/

		for (int i = x - maxPO; i <= x + maxPO; i++) {
			for (int j = y - maxPO; j <= y + maxPO; j++) {
				targettableCells.push_back(Point2D(i, j));
			}
		}
	}
	if (type == TypeZoneLaunch::NORMAL) {
		targettableCells.push_back(Point2D(x + 3, y + 2));
		targettableCells.push_back(Point2D(x + 3, y - 2));
		targettableCells.push_back(Point2D(x + 1, y + 2));
		targettableCells.push_back(Point2D(x + 1, y - 2));
	}



	return targettableCells;
}

bool ZoneAndSightCalculator::isObstacle(int x, int y, std::vector<Obstacle> obstacles)
{
	bool bObstacle = false;
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (obstacles[i].getX() == x && obstacles[i].getY() == y)
		{
			bObstacle = true;
			break;
		}
	}

	return bObstacle;
}

std::vector<Point2D> ZoneAndSightCalculator::processLineOfSight(int launcherX, int launcherY, std::vector<Point2D> cellsToTest, std::vector<Obstacle> obstacles)
{
	std::vector<Point2D> targettableCells;

	/*int targetX, targetY = 0;
	int screenSizeX, screenSizeY, a, b, y;
	for (targetX = 0; targetX < screenSizeX; targetX++) {
		a = (targetY - launcherY) / (targetX - launcherX);
		b = launcherY - (launcherX * a);
		if (targetX > launcherX) {
			for (int i = launcherX; i < targetX; i++) {
				y = a * i + b;
				if (this->isObstacle(i,y,obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
		if (targetX < launcherX) {
			for (int i = launcherX; i > targetX; i--) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
	}
	targetY = screenSizeY;
	for (targetX = 0; targetX < screenSizeX; targetX++) {
		a = (targetY - launcherY) / (targetX - launcherX);
		b = launcherY - (launcherX * a);
		if (targetX > launcherX) {
			for (int i = launcherX; i < targetX; i++) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
		if (targetX < launcherX) {
			for (int i = launcherX; i > targetX; i--) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
	}
	targetX = 0;
	for (targetY = 0; targetY < screenSizeY; targetY++) {
		a = (targetY - launcherY) / (targetX - launcherX);
		b = launcherY - (launcherX * a);
		if (targetY > launcherY) {
			for (int i = launcherY; i < targetY; i++) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
		if (targetY < launcherY) {
			for (int i = launcherY; i > targetY; i--) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
	}
	targetX = screenSizeX;
	for (targetY = 0; targetY < screenSizeY; targetY++) {
		a = (targetY - launcherY) / (targetX - launcherX);
		b = launcherY - (launcherX * a);
		if (targetY > launcherY) {
			for (int i = launcherY; i < targetY; i++) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
		if (targetY < launcherY) {
			for (int i = launcherY; i > targetY; i--) {
				y = a * i + b;
				if (this->isObstacle(i, y, obstacles) == true) {
					break;
				}
				else {
					targettableCells.push_back(Point2D(i, y));
				}
			}
		}
	}*/

	for (int i = 0; i < cellsToTest.size(); i++) {
		int targetX = cellsToTest[i].getX();
		int targetY = cellsToTest[i].getY();
		double a, b;
		if (targetX != launcherX) {
			a = (double)(targetY - launcherY) / (double)(targetX - launcherX);
			b = launcherY - (launcherX * a);
		}
		else {
			a = 0;
			b = 0;
		}
		int y, y1, x;
		if (targetX > launcherX) {
			for (int x = launcherX; x <= targetX; x++) {
				if (a > -0.5 && a < 0.5) {
					y = floor(a * x + b);
					if (this->isObstacle(x, y, obstacles) == true) {
						break;
					}
					else if (x == targetX && y == targetY) {
						targettableCells.push_back(Point2D(x, y));
					}
				}
				else {
					y = ceil(a * x + b);
					y1 = floor(a * x + b);
					if (this->isObstacle(x, y, obstacles) == true) {
						break;
					}
					else if (x == targetX && y == targetY) {
						targettableCells.push_back(Point2D(x, y));
					}
					if (this->isObstacle(x, y1, obstacles) == true) {
						break;
					}
					else if (x == targetX && y1 == targetY) {
						targettableCells.push_back(Point2D(x, y1));
					}
				}
			}
		}
		else if (targetX < launcherX) {
			for (int x = launcherX; x >= targetX; x--) {
				if (a > -0.5 && a < 0.5) {
					y = floor(a * x + b);
					if (this->isObstacle(x, y, obstacles) == true) {
						break;
					}
					else if(x == targetX && y == targetY){
						targettableCells.push_back(Point2D(x, y));
					}
				}
				else {
					y = ceil(a * x + b);
					y1 = floor(a * x + b);
					if (this->isObstacle(x, y, obstacles) == true) {
						break;
					}
					else if (x == targetX && y == targetY) {
						targettableCells.push_back(Point2D(x, y));
					}
					if (this->isObstacle(x, y1, obstacles) == true) {
						break;
					}
					else if (x == targetX && y1 == targetY) {
						targettableCells.push_back(Point2D(x, y1));
					}
				}
			}
		}
		else if (targetX == launcherX) {
			if (targetY > launcherY) {
				for (int y = launcherY; y <= targetY; y++) {
					if (this->isObstacle(targetX, y, obstacles) == true) {
						break;
					}
					else if (y == targetY) {
						targettableCells.push_back(Point2D(targetX, y));
					}
				} 
			}
			else if (targetY < launcherY) {
				for (int y = launcherY; y >= targetY; y--) {
					if (this->isObstacle(targetX, y, obstacles) == true) {
						break;
					}
					else if (y == targetY) {
						targettableCells.push_back(Point2D(targetX, y));
					}
				}
			}
		}
	}
	return targettableCells;
}