#pragma once
#include <MoveActionAnimationEventListener.h>
#include "BattleActionToAnimation.h"
#include "IScreenActionCallback.h"

class CharacterDieAction :  public BattleActionToAnimation, MoveActionAnimationEventListener
{
private:
	int persoId;
	bool moveAnimationFinished;
	IScreenActionCallback * screen;
	bool firstUpdate;
	bool hasResetAttackAnimation;
public:
	CharacterDieAction(IScreenActionCallback * screen, int persoId)
	{
		this->persoId = persoId;
		this->screen = screen;
		moveAnimationFinished = false;
		firstUpdate = true;
		hasResetAttackAnimation = false;
	}

	virtual void update(float deltatime)
	{
		elapseTime(deltatime);
		if (firstUpdate)
		{
			tw::Player * srcPlayer = screen->getCharacter(persoId);
			srcPlayer->getCharacter()->startDieAction(1);
			firstUpdate = false;
		}

		if (getEllapsedTime() > 1000 && !hasResetAttackAnimation)
		{
			tw::Player * srcPlayer = screen->getCharacter(persoId);
			srcPlayer->getCharacter()->resetAnimation();
			hasResetAttackAnimation = true;

			screen->applyCharacterDie(persoId);
			notifyAnimationFinished(0);
			delete this;
		}
	}

	virtual void onMoveFinished()
	{
		moveAnimationFinished = true;
		notifyAnimationFinished(0);
	}

};

