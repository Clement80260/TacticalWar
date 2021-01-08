#pragma once
#include "Point2D.h"

namespace tw
{
	class CellData;
	class BaseCharacterModel;

	class Obstacle : public Point2D
	{
		bool isTargettable;

	public:
		Obstacle(CellData * cell);
		Obstacle(BaseCharacterModel * character);
		~Obstacle();

		inline bool getIsTargettable() {
			return isTargettable;
		}
	};
}