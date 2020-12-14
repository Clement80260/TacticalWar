#pragma once

#include <map>
#include <vector>
#include "CellData.h"
#include "Obstacle.h"

namespace tw
{
	class Environment
	{
	private:
		int width;
		int height;
		std::map<int, std::map<int, CellData*>> mapData;

		std::vector<Obstacle> staticObstacles;
		bool obstacleCacheInitDone;

		int id;

	public:
		Environment(int width, int height, int environmentId);
		CellData* getMapData(int x, int y);
		std::vector<tw::Obstacle> getObstacles()
		{
			if (!obstacleCacheInitDone)
			{
				for (int i = 0; i < getWidth(); i++)
				{
					for (int j = 0; j < getHeight(); j++)
					{
						CellData * c = getMapData(i, j);
						if (c->getIsObstacle())
						{
							staticObstacles.push_back(Obstacle(c));
						}
					}
				}
				obstacleCacheInitDone = true;
			}

			return staticObstacles;
		}

		inline int getWidth() { return width; }
		inline int getHeight() { return height; }

		inline int getId() { return id; }
	};
}

