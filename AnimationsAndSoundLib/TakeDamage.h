#pragma once
#include <MoveActionAnimationEventListener.h>
#include "BattleActionToAnimation.h"
#include "IScreenActionCallback.h"

class TakeDamage : public BattleActionToAnimation, MoveActionAnimationEventListener
{
private:
	int persoId;
	int x, y;
	bool moveAnimationFinished;
	IScreenActionCallback * screen;
	bool firstUpdate;
	int damage;

	bool hasResetAttackAnimation;
public:
	TakeDamage(IScreenActionCallback * screen, int persoId, int damage)
	{
		this->persoId = persoId;
		this->screen = screen;
		moveAnimationFinished = false;
		firstUpdate = true;
		hasResetAttackAnimation = false;
		this->damage = damage;
	}

	virtual void update(float deltatime)
	{
		elapseTime(deltatime);
		if (firstUpdate)
		{
			tw::BaseCharacterModel * srcPlayer = screen->getCharacter(persoId);

			srcPlayer->modifyCurrentLife(-damage);
			if (!srcPlayer->isAlive())
			{
				srcPlayer->startDieAction(1);
			}
			else
			{
				srcPlayer->startTakeDmg(1);
			}
			firstUpdate = false;
		}

		if (getEllapsedTime() > 1000 && !hasResetAttackAnimation)
		{
			tw::BaseCharacterModel * srcPlayer = screen->getCharacter(persoId);
			srcPlayer->resetAnimation();
			hasResetAttackAnimation = true;
			screen->applyTakeDamage(persoId);
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

