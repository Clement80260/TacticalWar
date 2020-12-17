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
		int x1 = x + minPO + 1;
		int y1 = y + minPO + 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 + 1;
			y1 = y1 + 1;
		}
		x1 = x - minPO - 1;
		y1 = y - minPO - 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 - 1;
			y1 = y1 - 1;

		}
		x1 = x + minPO + 1;
		y1 = y - minPO - 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 + 1;
			y1 = y1 - 1;

		}
		x1 = x - minPO - 1;
		y1 = y + minPO + 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 - 1;
			y1 = y1 + 1;

		}
	}

	if (type == TypeZoneLaunch::STAR) {
		int x1 = x + minPO + 1;
		int y1 = y + minPO + 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 + 1;
			y1 = y1 + 1;
		}
		x1 = x - minPO - 1;
		y1 = y - minPO - 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 - 1;
			y1 = y1 - 1;

		}
		x1 = x + minPO + 1;
		y1 = y - minPO - 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 + 1;
			y1 = y1 - 1;

		}
		x1 = x - minPO - 1;
		y1 = y + minPO + 1;
		for (i = 0; i < maxPO; i++) {
			targettableCells.push_back(Point2D(x1, y1));
			x1 = x1 - 1;
			y1 = y1 + 1;

		}

		for (i = x + minPO + 1; i <= x + minPO + maxPO; i++) {
			targettableCells.push_back(Point2D(i, y));
		}
		for (i = x - minPO - 1; i >= x - minPO - maxPO; i--) {
			targettableCells.push_back(Point2D(i, y));
		}
		for (i = y + minPO + 1; i <= y + minPO + maxPO; i++) {
			targettableCells.push_back(Point2D(x, i));
		}
		for (i = y - minPO - 1; i >= y - minPO - maxPO; i--) {
			targettableCells.push_back(Point2D(x, i));
		}
	}
	if (type == TypeZoneLaunch::NORMAL) {
		for (i = y + minPO + 1; i < y + minPO + maxPO + 1; i++) {
			for (int j = x - minPO - maxPO; j < x + minPO + maxPO + 1; j++) {
				targettableCells.push_back(Point2D(j, i));
			}
		}
		for (i = y - minPO - 1; i > y - minPO - maxPO - 1; i--) {
			for (int j = x - minPO - maxPO; j < x + minPO + maxPO + 1; j++) {
				targettableCells.push_back(Point2D(j, i));
			}
		}
		for (i = x + minPO + 1; i < x + minPO + maxPO + 1; i++) {
			for (int j = y - minPO - maxPO; j < y + minPO + maxPO; j++) {
				targettableCells.push_back(Point2D(i, j));
			}
		}
		for (i = x - minPO - 1; i > x - minPO - maxPO - 1; i--) {
			for (int j = y - minPO - maxPO; j < y + minPO + maxPO + 1; j++) {
				targettableCells.push_back(Point2D(i, j));
			}
		}
	}



	return targettableCells;
}

int ZoneAndSightCalculator::isObstacle(int x, int y, std::vector<Obstacle> obstacles)
{
	int bObstacle = 0;
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (obstacles[i].getX() == x && obstacles[i].getY() == y)
		{
			if (obstacles[i].getIsTargettable() == true) {
				bObstacle = 2;
			}
			else {
				bObstacle = 1;
			}
			break;
		}
	}

	return bObstacle;
}

std::vector<Point2D> ZoneAndSightCalculator::processLineOfSight(int launcherX, int launcherY, std::vector<Point2D> cellsToTest, std::vector<Obstacle> obstacles)
{
	std::vector<Point2D> targettableCells;

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
					if (this->isObstacle(x, y, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(x, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(x, y));
						break;
					}
					else if (x == targetX && y == targetY) {
						targettableCells.push_back(Point2D(x, y));
					}
				}
				else {
					y = ceil(a * x + b);
					y1 = floor(a * x + b);
					if (this->isObstacle(x, y, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(x, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(x, y));
						break;
					}
					else if (x == targetX && y == targetY) {
						targettableCells.push_back(Point2D(x, y));
					}
					if (this->isObstacle(x, y1, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(x, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(x, y));
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
					if (this->isObstacle(x, y, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(x, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(x, y));
						break;
					}
					else if(x == targetX && y == targetY){
						targettableCells.push_back(Point2D(x, y));
					}
				}
				else {
					y = ceil(a * x + b);
					y1 = floor(a * x + b);
					if (this->isObstacle(x, y, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(x, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(x, y));
						break;
					}
					else if (x == targetX && y == targetY) {
						targettableCells.push_back(Point2D(x, y));
					}
					if (this->isObstacle(x, y1, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(x, y1, obstacles) == 2) {
						targettableCells.push_back(Point2D(x, y1));
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
					if (this->isObstacle(targetX, y, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(targetX, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(targetX, y));
						break;
					}
					else if (y == targetY) {
						targettableCells.push_back(Point2D(targetX, y));
					}
				} 
			}
			else if (targetY < launcherY) {
				for (int y = launcherY; y >= targetY; y--) {
					if (this->isObstacle(targetX, y, obstacles) == 1) {
						break;
					}
					else if (this->isObstacle(targetX, y, obstacles) == 2) {
						targettableCells.push_back(Point2D(targetX, y));
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