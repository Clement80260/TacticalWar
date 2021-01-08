#include "MapClickListener.h"
#include <ZoneAndSightCalculator.h>
#include <iostream>
#include <Point2D.h>

MapClickListener::MapClickListener(tw::Environment * e, TestColorator * colorator)
{
	this->colorator = colorator;
	this->environment = e;
	startPointSelected = false;
	endPointSelected = false;
}

MapClickListener::~MapClickListener()
{

}

void MapClickListener::onCellClicked(int x, int y)
{
	std::cout << "Cellule click x=" << x << ", y=" << y << std::endl;

	if (!startPointSelected)
	{
		std::cout << "Set startCell" << std::endl;
		startCell.setX(x);
		startCell.setY(y);
		startPointSelected = true;
	}

	std::vector<tw::Point2D> zoneToTest = tw::ZoneAndSightCalculator::getInstance()->generateZone(x, y, 2, 4, TypeZoneLaunch::NORMAL);
	colorator->setPathToHighlight(zoneToTest);
	//colorator->setPathToHighlight(tw::ZoneAndSightCalculator::getInstance()->processLineOfSight(x, y, zoneToTest, environment->getObstacles()));
	/*
	else if (!endPointSelected)
	{
		std::cout << "Set endCell" << std::endl;
		endCell.setX(x);
		endCell.setY(y);
		endPointSelected = true;

		processedPath = tw::Pathfinder::getInstance()->getPath(startCell, endCell, environment, std::vector<tw::Obstacle*>());
		colorator->setPathToHighlight(processedPath);
	}
	else
	{
		std::cout << "Clear path" << std::endl;
		startPointSelected = false;
		endPointSelected = false;
		processedPath.clear();
		colorator->setPathToHighlight(processedPath);
	}*/
}

void MapClickListener::onCellHover(int x, int y)
{
}

void MapClickListener::onCellMouseDown(int x, int y)
{
}
