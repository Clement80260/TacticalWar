#pragma once
#include "NoDurationAction.h"
#include "IScreenActionCallback.h"

class SynchroPAAction : public NoDurationAction
{
	IScreenActionCallback * screen;
	int persoId;
	int pa;

public:
	SynchroPAAction(IScreenActionCallback * screen, int persoId, int pa)
	{
		this->screen = screen;
		this->persoId = persoId;
		this->pa = pa;
	}

	virtual void update()
	{
		screen->applySynchroPA(persoId, pa);
	}
};

