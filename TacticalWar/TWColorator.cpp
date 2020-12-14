#include "TWColorator.h"


sf::Color TWColorator::getColorForCell(tw::CellData * cell)
{
	if (state == BattleState::BATTLE_PHASE)
	{
		if (spellLaunchZone.size() > 0)
		{
			for (int i = 0; i < spellLaunchZone.size(); i++)
			{
				if ((*cell) == spellLaunchZone[i])
				{
					return sf::Color(50, 200, 255);
				}
			}
		}
		else
		{
			if (cell->getIsWalkable() && !cell->getIsObstacle())
			{
				for (int i = 0; i < pathToHighlight.size(); i++)
				{
					if ((*cell) == pathToHighlight[i])
					{
						return getPathHighlightColor();
					}
				}

				for (int i = 0; i < pathZone.size(); i++)
				{
					if ((*cell) == pathZone[i])
					{
						return getPathZoneColor();
					}
				}
			}
		}
	}
	else if (state == BattleState::PREPARATION_PHASE)
	{
		if (cell->isTeam1StartPoint())
		{
			return sf::Color(50, 200, 255);
		}
		else if (cell->isTeam2StartPoint())
		{
			return sf::Color(255, 50, 50);
		}
	}

	return sf::Color::White;
}