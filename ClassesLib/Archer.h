#pragma once

#include <BaseCharacterModel.h>
#include <Environment.h>

class Archer : public tw::BaseCharacterModel
{
public:

	virtual int getClassId()
	{
		return 2;
	}

	virtual std::string getName()
	{
		return "Archer";
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
		return 4;
	}

	virtual int getBaseAttack()
	{
		return 5;
	}

	virtual int getBaseDefense()
	{
		return 0;
	}



	//Passif : +1 de PD - fonction inutilisée
	virtual bool doAttack1(int targetX, int targetY)
	{
		return false;
	}

	//Sort 1 : Flèche toxique : (Mana : 4 / Ligne 3x1 / DPS : 10 / Malus -3 HP / tour pendant 2 tour / Cd : 4t)
	virtual bool doAttack2(int targetX, int targetY)
	{

		return true;
	}

	//Sort 2 : Flèche repousse (Mana : 3 / Ligne 3x1 / DPS : 4 / Repousse de 2 cases / Cd : 3t)
	virtual bool doAttack3(int targetX, int targetY)
	{
		return true;
	}

	//Sort 3 : Tir précis (Mana : 2 / Ligne 4x1 / DPS : 7 / Cd : 1t)
	virtual bool doAttack4(int targetX, int targetY)
	{
		return true;
	}

	//Auto attaque (Mana : 0 / Corps à corps / DPS : 5 / Cd : 0t)
	virtual bool doAttack5(int targetX, int targetY)
	{
		return true;
	}

	Archer(tw::Environment * environment, int teamId, int currentX, int currentY)
		: BaseCharacterModel(environment, teamId, currentX, currentY)
	{

	}
};

