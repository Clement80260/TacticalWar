#include "pch.h"
#include "CharacterFactory.h"
#include <stdlib.h>

#include "Mage.h"
#include "Archer.h"
#include "Protecteur.h"
#include "Guerrier.h"
#include <ZoneAndSightCalculator.h>

CharacterFactory * CharacterFactory::instance = NULL;

CharacterFactory * CharacterFactory::getInstance()
{
	if (instance == NULL)
		instance = new CharacterFactory();

	return instance;
}

tw::BaseCharacterModel * CharacterFactory::constructCharacter(tw::Environment * environment, int classId, int teamId, int posX, int posY, tw::IMapKnowledge * map)
{
	tw::BaseCharacterModel * character = NULL;
	switch (classId)
	{
	case 1:	// Mage
		character =  new Mage(environment, teamId, posX, posY, map);
		break;

	case 2:	// Archer
		character = new Archer(environment, teamId, posX, posY, map);
		break;

	case 3:	// Protecteur
		character = new Protecteur(environment, teamId, posX, posY, map);
		break;

	case 4:	// Guerrier
		character = new Guerrier(environment, teamId, posX, posY, map);
		break;
	}

	if (character != NULL)
		character->setZoneCalculator(tw::ZoneAndSightCalculator::getInstance());

	return character;
}