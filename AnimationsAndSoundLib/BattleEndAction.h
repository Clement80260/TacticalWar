#pragma once
#include "NoDurationAction.h"
#include "IScreenActionCallback.h"

class BattleEndAction : public NoDurationAction
{
	IScreenActionCallback * screen;
	int teamId;
	int pa;

public:
	BattleEndAction(IScreenActionCallback * screen, int teamId)
	{
		this->screen = screen;
		this->teamId = teamId;
	}

	virtual void update()
	{
		screen->applyEndOfBattle(teamId);
	}
};

