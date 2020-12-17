#pragma once
#include <Point2D.h>
#include <vector>
#include <Obstacle.h>
#include <TypeZoneLaunch.h>
#include <IZoneAndSightCalculator.h>

namespace tw
{
	class ZoneAndSightCalculator : public IZoneAndSightCalculator
	{
	private:
		ZoneAndSightCalculator();
		~ZoneAndSightCalculator();
		static ZoneAndSightCalculator * instance;

		int isObstacle(int x, int y, std::vector<Obstacle> obstacles);

	public:
		static ZoneAndSightCalculator * getInstance();

		std::vector<Point2D> generateZone(int x, int y, int minPO, int maxPO, TypeZoneLaunch type);
		std::vector<Point2D> processLineOfSight(int launcherX, int launcherY, std::vector<Point2D> cellsToTest, std::vector<Obstacle> obstacles);
	};

}