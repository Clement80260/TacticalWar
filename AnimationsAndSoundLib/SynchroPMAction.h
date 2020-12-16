#pragma once
#include "NoDurationAction.h"
#include "IScreenActionCallback.h"

class SynchroPMAction : public NoDurationAction
{
	IScreenActionCallback * screen;
	int persoId;
	int pm;

public:
	SynchroPMAction(IScreenActionCallback * screen, int persoId, int pm)
	{
		this->screen = screen;
		this->persoId = persoId;
		this->pm = pm;
	}

	virtual void update()
	{
		screen->applySynchroPM(persoId, pm);
	}
};

