#pragma once

#include <BaseCharacterModel.h>
#include <Environment.h>

class Mage : public tw::BaseCharacterModel
{
public:
	virtual int getClassId()
	{
		return 1;
	}

	virtual std::string getName()
	{
		return "Mage";
	}

	virtual std::string getGraphicsPath()
	{
		return "./assets/Warrior/";
	}

	// Retourne la valeur du maximum de point de vie de base (sans altération d'effet). C'est une caractéristique de base de la classe.
	virtual int getBaseMaxLife()
	{
		return 80;
	}

	//Fonction à ajouter
	virtual int getBasePa()
	{
		return 6;
	}

	//Fonction à ajouter
	virtual int getBasePm()
	{
		return 3;
	}

	virtual int getBaseAttack()
	{
		return 5;
	}

	virtual int getBaseDefense()
	{
		return 0;
	}


	//Passif : Réduction de mana pour les alliés dans la zone 3x3
	virtual bool doAttack1(int targetX, int targetY)
	{
		return true;
	}

	//Sort 1 : Boule de feu (Mana : 4 / Zone étoile / DPS : 15-10(45%-25% de brûlure / Cd : 3t)
	virtual bool doAttack2(int targetX, int targetY)
	{
		
		return true;
	}

	//Sort 2 : Eclair (Mana : 2 / Zone unique / DPS : 6 / Cd : 1t)
	virtual bool doAttack3(int targetX, int targetY)
	{
		return true;
	}

	//Sort 3 : Blizzard (Mana : 3 / Joueur au centre : carré de 3x3 autour du joueur / DPS : )
	virtual bool doAttack4(int targetX, int targetY)
	{
		return true;
	}

	virtual bool doAttack5(int targetX, int targetY)
	{
		return true;
	}

	Mage(tw::Environment * environment, int teamId, int currentX, int currentY)
		: BaseCharacterModel(environment, teamId, currentX, currentY)
	{

	}
};

