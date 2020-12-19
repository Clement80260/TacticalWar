#pragma once

#include "NoDurationAction.h"
#include "IScreenActionCallback.h"

class TeleportAction : public NoDurationAction
{
	IScreenActionCallback * screen;
	int persoId;
	int cellX;
	int cellY;

public:
	TeleportAction(IScreenActionCallback * screen, int persoId, int cellX, int cellY)
	{
		this->screen = screen;
		this->persoId = persoId;
		this->cellX = cellX;
		this->cellY = cellY;
	}

	virtual void update()
	{
		screen->applyTeleport(persoId, cellX, cellY);
	}
};

