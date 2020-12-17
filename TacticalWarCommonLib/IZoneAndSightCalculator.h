#pragma once
#include <vector>
#include "Point2D.h"
#include "Obstacle.h"
#include "TypeZoneLaunch.h"

class IZoneAndSightCalculator
{
public:
	virtual std::vector<tw::Point2D> generateZone(int x, int y, int minPO, int maxPO, TypeZoneLaunch type) = 0;
	virtual std::vector<tw::Point2D> processLineOfSight(int launcherX, int launcherY, std::vector<tw::Point2D> cellsToTest, std::vector<tw::Obstacle> obstacles) = 0;
};

