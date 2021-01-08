#pragma once
#include <string>
#include <Player.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Point2D.h>
#include <MoveActionAnimationEventListener.h>
#include "SpellView.h"

class IScreenActionCallback
{
public:
	virtual void applyEndOfBattle(int winnerTeam) = 0;
	virtual void applyChangeTurn(float remaining, int idPerso, std::string message) = 0;
	virtual void applyCharacterDie(int idPerso) = 0;
	virtual void applyCharacterLaunchSpell(int persoId, int x, int y, int spellId) = 0;
	virtual tw::BaseCharacterModel* getCharacter(int persoId) = 0;
	virtual std::vector <tw::BaseCharacterModel*> getAliveCharacters() = 0;
	virtual void addAnimationToDisplay(SpellView * s) = 0;
	virtual void applyCharacterMove(int persoId, std::vector<tw::Point2D> path, MoveActionAnimationEventListener * callback) = 0;
	virtual void applyCharacterDisconnected(int persoId) = 0;
	virtual void applyCharacterConnected(int persoId) = 0;
	virtual void applyTakeDamage(int persoId) = 0;
	virtual void applyCharacterPosition(int persoId, int x, int y) = 0;
	virtual void applyEnterBattlePhase() = 0;
	virtual void applyTeleport(int playerId, int cellX, int cellY) = 0;
	virtual void applySynchroPA(int playerId, int pa) = 0;
	virtual void applySynchroPM(int playerId, int pm) = 0;
	virtual void playTakeDamageSound() = 0;
};
