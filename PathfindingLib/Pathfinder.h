#pragma once

#include <vector>
#include <Environment.h>
#include <Obstacle.h>
#include <string>
#include <StringUtils.h>

namespace tw
{
	enum class Orientation {
		BOTTOM_RIGHT,
		TOP_RIGHT,
		TOP_LEFT,
		BOTTOM_LEFT
	};

	/*
	class Position
	{
	private:
		int x;
		int y;

	public:
		inline Position(int x, int y)
			: x(x), y(y)
		{}

		inline void setX(int x) {
			this->x = x;
		}

		inline void setY(int y) {
			this->y = y;
		}

		inline int getX() {
			return x;
		}

		inline int getY() {
			return y;
		}
	};
	*/

	
	
	class Pathfinder
	{
	private:
		Pathfinder();
		~Pathfinder();

		static Pathfinder * instance;

	public:

		static Pathfinder * getInstance();

		Orientation getOrientationFromPosition(Point2D p1, Point2D p2);
		std::vector<Point2D> getPath(Point2D startPosition, Point2D endPosition, Environment * environment, std::vector<Obstacle> obstacles);
		bool isNotDynamicObstacle(CellData * voisinDroite, std::vector<Obstacle> obstacles);
		int TotalCostFromStartToEnd();

		static std::string serializePath(std::vector<Point2D> path)
		{
			std::string pathStr = "";

			for (int i = 0; i < path.size(); i++)
			{
				if (i > 0)
					pathStr += ",";
				pathStr += std::to_string(path[i].getX()) + "^" + std::to_string(path[i].getY());
			}

			return pathStr;
		}

		static std::vector<Point2D> deserializePath(std::string pathStr)
		{
			std::vector<Point2D> path;

			std::vector<std::string> pathData = StringUtils::explode(pathStr, ',');
			for (int i = 0; i < pathData.size(); i++)
			{
				std::vector<std::string> nodeData = StringUtils::explode(pathData[i], '^');
				int x = std::atoi(nodeData[0].c_str());
				int y = std::atoi(nodeData[1].c_str());
				path.push_back(Point2D(x, y));
			}

			return path;
		}
	};
}
