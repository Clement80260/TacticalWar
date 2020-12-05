#pragma once

#include <BaseCharacterModel.h>
#include <Environment.h>

class Archer : public tw::BaseCharacterModel
{
private:

	int tour = 1;
	int compt1, compt2, compt3;

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

	virtual int getAttack1()
	{
		return compt1;
	}

	virtual int getAttack2()
	{
		return compt2;
	}

	virtual int getAttack3()
	{
		return compt3;
	}

	virtual void turnStart()
	{
		// Décrémentation des cooldowns :
		if (compt1 > 0)
			compt1--;
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

	//Sort 2 : Flèche repousse (Mana : 3 / Ligne 2x1 / DPS : 4 / Repousse de 2 cases / Cd : 3t)
	virtual bool doAttack3(int targetX, int targetY)
	{
		return true;
	}

	//Sort 3 : Tir précis (Mana : 2 / Ciblable(zone 3x3) / DPS : 7 / Cd : 1t)
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
		compt1 = 4;
		compt2 = 3;
		compt3 = 1;
	}


	// Méthodes rajoutées :	TYPE DE CLASSE

	virtual std::string getClassName()
	{
		return "Archer";
	}

	virtual std::string getClassDescription()
	{
		return " Personnage distance avec des attaques de malus";
	}

	virtual std::string getClassIconPath()
	{
		return "./assets/classicons/Chasseur.png";
	}


	//------------------------------------	NOM SPELL

	virtual std::string getSpell1Name()
	{
		return "Flèche toxique";
	}

	virtual std::string getSpell2Name()
	{
		return "Flèche repousse";
	}

	virtual std::string getSpell3Name()
	{
		return "Tir précis";
	}

	virtual std::string getSpell4Name()
	{
		return " Attaque de base";
	}


	//------------------------------------	DESCRIPTION SPELL
	virtual std::string getSpell1Description()
	{
		return "Archer, inflige 10 de dégâts et empoisonne sur 2 tours";
	}

	virtual std::string getSpell2Description()
	{
		return "Archer, inflige 4 de dégâts et repousse la cible de 2 cases";
	}

	virtual std::string getSpell3Description()
	{
		return "Archer, inflige 6 de dégâts et ignore les obstacles";
	}

	virtual std::string getSpell4Description()
	{
		return "Archer, inflige 5 de dégâts";
	}


	//------------------------------------	ICON SPELL
	virtual std::string getSpell1IconPath()
	{
		return "./assets/spellicons/101.png";
	}

	virtual std::string getSpell2IconPath()
	{
		return "./assets/spellicons/515.png";
	}

	virtual std::string getSpell3IconPath()
	{
		return "./assets/spellicons/516.png";
	}

	virtual std::string getSpell4IconPath()
	{
		return "./assets/spellicons/700.png";
	}


	//------------------------------------	EFFET DES SPELLS
	virtual std::vector<Effect> getSpell1Effects()
	{
		std::vector<Effect> effects;

		return effects;
	}

	virtual std::vector<Effect> getSpell2Effects()
	{
		std::vector<Effect> effects;

		return effects;
	}

	virtual std::vector<Effect> getSpell3Effects()
	{
		std::vector<Effect> effects;

		return effects;
	}

	virtual std::vector<Effect> getSpell4Effects()
	{
		std::vector<Effect> effects;

		return effects;
	}


	//------------------------------------ NOMBRE DE MANA PAR SPELL (PA)
	virtual int getSpell1ManaCost()
	{
		return 4;
	}

	virtual int getSpell2ManaCost()
	{
		return 3;
	}

	virtual int getSpell3ManaCost()
	{
		return 2;
	}

	virtual int getSpell4ManaCost()
	{
		return 1;
	}

	//------------------------------------ PORTÉE MAX D'UNE SPELL
	virtual int getSpell1MinPO()
	{
		return 1;
	}

	virtual int getSpell2MinPO()
	{
		return 1;
	}

	virtual int getSpell3MinPO()
	{
		return 1;
	}

	virtual int getSpell4MinPO()
	{
		return 1;
	}

	//------------------------------------ PORTÉE MAX D'UN SPELL

	virtual int getSpell1MaxPO()
	{
		return 3;
	}

	virtual int getSpell2MaxPO()
	{
		return 2;
	}

	virtual int getSpell3MaxPO()
	{
		return 3;
	}

	virtual int getSpell4MaxPO()
	{
		return 12;
	}

	//------------------------------------ JE SAIS PAS X)

	virtual TypeZoneLaunch getSpell1LaunchZoneType()
	{
		return TypeZoneLaunch::LINE;
	}

	virtual TypeZoneLaunch getSpell2LaunchZoneType()
	{
		return TypeZoneLaunch::NORMAL;
	}

	virtual TypeZoneLaunch getSpell3LaunchZoneType()
	{
		return TypeZoneLaunch::DIAGONAL;
	}

	virtual TypeZoneLaunch getSpell4LaunchZoneType()
	{
		return TypeZoneLaunch::STAR;
	}

	//------------------------------------ // TYPE SPELLS IMPACT ZONE

	virtual TypeZoneLaunch getSpell1ImpactZoneType()
	{
		return TypeZoneLaunch::NORMAL;
	}

	virtual TypeZoneLaunch getSpell2ImpactZoneType()
	{
		return TypeZoneLaunch::NORMAL;
	}

	virtual TypeZoneLaunch getSpell3ImpactZoneType()
	{
		return TypeZoneLaunch::NORMAL;
	}

	virtual TypeZoneLaunch getSpell4ImpactZoneType()
	{
		return TypeZoneLaunch::NORMAL;
	}

	//------------------------------------ // ZONE D'IMPACT MIN PO SORTS

	virtual int getSpell1ImpactZoneMinPO()
	{
		return 0;
	}

	virtual int getSpell2ImpactZoneMinPO()
	{
		return 0;
	}

	virtual int getSpell3ImpactZoneMinPO()
	{
		return 0;
	}

	virtual int getSpell4ImpactZoneMinPO()
	{
		return 0;
	}

	//------------------------------------  // ZONE D'IMPACT MAX PO SORTS

	virtual int getSpell1ImpactZoneMaxPO()
	{
		return 0;
	}

	virtual int getSpell2ImpactZoneMaxPO()
	{
		return 0;
	}

	virtual int getSpell3ImpactZoneMaxPO()
	{
		return 0;
	}

	virtual int getSpell4ImpactZoneMaxPO()
	{
		return 0;
	}

	//--------------------------------------------------------------------
};

