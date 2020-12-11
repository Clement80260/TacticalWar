#pragma once

#include <CellColorator.h>
#include <Point2D.h>
#include <Battle.h>

class TWColorator : public tw::CellColorator
{
	std::vector<tw::Point2D> pathZone;
	std::vector<tw::Point2D> pathToHighlight;
	sf::Color pathZoneColor;
	sf::Color pathHighlightColor;
	BattleState state;

public:
	TWColorator(sf::Color pathZoneColor, sf::Color pathHighlightColor)
	{
		this->pathZoneColor = pathZoneColor;
		this->pathHighlightColor = pathHighlightColor;
		this->state = BattleState::WAITING_PLAYER_PHASE;
	}

	virtual sf::Color getColorForCell(tw::CellData * cell);

	void setPathZone(std::vector<tw::Point2D> pathZone)
	{
		this->pathZone = pathZone;
	}

	sf::Color getPathZoneColor() { return pathZoneColor; }


	void setPathToHighlight(std::vector<tw::Point2D> pathToHighlight)
	{
		this->pathToHighlight = pathToHighlight;
	}

	sf::Color getPathHighlightColor() { return pathHighlightColor; }

	BattleState getBattleState()
	{
		return state;
	}

	void setBattleState(BattleState state)
	{
		this->state = state;
	}
};

