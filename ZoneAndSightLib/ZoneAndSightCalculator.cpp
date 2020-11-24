#include "pch.h"
#include "ZoneAndSightCalculator.h"
#include <iostream>

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
		int x1, y1;

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
		}
	}

	return targettableCells;
}

std::vector<Point2D> ZoneAndSightCalculator::processLineOfSight(int launcherX, int launcherY, std::vector<Point2D> cellsToTest, std::vector<Obstacle*> obstacles)
{
	std::vector<Point2D> targettableCells;


	return targettableCells;
}