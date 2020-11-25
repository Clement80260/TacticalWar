#pragma once
#include <MoveActionAnimationEventListener.h>
#include "BattleActionToAnimation.h"
#include "IScreenActionCallback.h"

class LaunchSpellAction : public BattleActionToAnimation, MoveActionAnimationEventListener
{
private:
	int persoId;
	int spellId;
	int x, y;
	bool moveAnimationFinished;
	IScreenActionCallback * screen;
	bool firstUpdate;
public:
	LaunchSpellAction(IScreenActionCallback * screen, int persoId,int x,int y)
	{
		this->persoId = persoId;
		this->screen = screen;
		this->x = x;
		this->y = y;
		moveAnimationFinished = false;
		firstUpdate = true;
	}

	virtual void update(float deltatime)
	{
		if (firstUpdate)
		{
			screen->applyCharacterLaunchSpell(persoId,x,y,spellId);
			firstUpdate = false;
		}
	}

	virtual void onMoveFinished()
	{
		moveAnimationFinished = true;
		notifyAnimationFinished(0);
	}
};