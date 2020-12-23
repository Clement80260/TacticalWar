#pragma once
#include <MoveActionAnimationEventListener.h>
#include "BattleActionToAnimation.h"
#include "IScreenActionCallback.h"
#include <SFML/Audio.hpp>

class LaunchSpellAction : public BattleActionToAnimation, MoveActionAnimationEventListener
{
private:
	int persoId;
	int spellId;
	int x, y;
	bool moveAnimationFinished;
	IScreenActionCallback * screen;
	bool firstUpdate;
	std::vector<tw::AttackDamageResult> impactedEntities;

	SpellView * spellView;

	bool hasResetAttackAnimation;
	bool hasResetTakeDamageAnimation;
public:
	LaunchSpellAction(IScreenActionCallback * screen, int persoId, int spellId, int x, int y)
	{
		this->persoId = persoId;
		this->spellId = spellId;
		this->screen = screen;
		this->x = x;
		this->y = y;
		moveAnimationFinished = false;
		firstUpdate = true;
		hasResetAttackAnimation = false;
		hasResetTakeDamageAnimation = false;

		spellView = NULL;
		std::string animPath = screen->getCharacter(persoId)->getSpellAnimationPath(spellId);
		if (animPath.size() > 0)
		{
			spellView = new SpellView(x, y);
			spellView->loadAnimation(animPath);
		}
	}

	~LaunchSpellAction()
	{
		if(spellView != NULL)
			delete spellView;
	}

	virtual void update(float deltatime)
	{
		elapseTime(deltatime);

		tw::BaseCharacterModel * spellLauncher = screen->getCharacter(persoId);

		if (firstUpdate)
		{
			impactedEntities = spellLauncher->doAttack(spellId, x, y);
			spellLauncher->startAttack1Animation(1);
			screen->applyCharacterLaunchSpell(persoId, x, y, spellId);	// Notifie le screen pour affichage dans les événements de combat ...
			firstUpdate = false;
		}

		if (getEllapsedTime() <= 1000)
		{
			if (spellView != NULL)
			{
				spellView->update(deltatime / 1000.0);
				screen->addAnimationToDisplay(spellView);
			}
		}

		if (getEllapsedTime() > 1000 && !hasResetAttackAnimation)
		{
			spellLauncher->resetAnimation();
			hasResetAttackAnimation = true;

			screen->playTakeDamageSound();

			for (int i = 0; i < impactedEntities.size(); i++)
			{
				tw::BaseCharacterModel * target = impactedEntities[i].getCharacter();
				int damage = impactedEntities[i].getDamage();
				if (target->getCurrentLife() <= damage)
				{
					target->startDieAction(1);
				}
				else
				{
					target->startTakeDmg(1);
				}
			}
		}

		if (getEllapsedTime() > 2000 && !hasResetTakeDamageAnimation)
		{
			for (int i = 0; i < impactedEntities.size(); i++)
			{
				impactedEntities[i].getCharacter()->resetAnimation();
				impactedEntities[i].getCharacter()->modifyCurrentLife(-impactedEntities[i].getDamage());	// Applique les dégats ...
			}
			hasResetTakeDamageAnimation = true;
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