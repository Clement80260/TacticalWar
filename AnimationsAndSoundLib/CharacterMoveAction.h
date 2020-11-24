#pragma once

#include <MoveActionAnimationEventListener.h>
#include "BattleActionToAnimation.h"

class CharacterMoveAction : public BattleActionToAnimation, MoveActionAnimationEventListener
{
private:
	bool moveAnimationFinished;
public:
	CharacterMoveAction(/**/)
	{
		moveAnimationFinished = false;
	}

	virtual void onMoveFinished()
	{
		moveAnimationFinished = true;
	}
};

