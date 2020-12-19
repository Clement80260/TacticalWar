#pragma once
#include <MoveActionAnimationEventListener.h>
#include "BattleActionToAnimation.h"
#include "IScreenActionCallback.h"
#include "NoDurationAction.h"

class ChangeTurnAction : public NoDurationAction
{
private:
	int persoId;
	float Remaining;
	std::string message;
	IScreenActionCallback * screen;

public:
	ChangeTurnAction(IScreenActionCallback * screen, int persoId, std::string message, float Remaining)
	{
		this->persoId = persoId;
		this->screen = screen;
		this->message = message;
		this->Remaining = Remaining;
	}

	virtual void update()
	{
		screen->applyChangeTurn(Remaining,persoId,message);
	}
};

