#include "pch.h"
#include "Obstacle.h"

#include "CellData.h"
#include "BaseCharacterModel.h"

using namespace tw;

Obstacle::Obstacle(CellData * cell)
	:
	Point2D(cell->getX(), cell->getY())
{
	isTargettable = false;
}

Obstacle::Obstacle(BaseCharacterModel * character)
	:
	Point2D(character->getCurrentX(), character->getCurrentY())
{
	isTargettable = true;
}

Obstacle::~Obstacle()
{
}
