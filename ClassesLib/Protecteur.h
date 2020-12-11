#pragma once

#include <BaseCharacterModel.h>
#include <Environment.h>

class Protecteur : public tw::BaseCharacterModel
{
private:

	int tour = 1;
	int compt1, compt2, compt3;

public:
	virtual int getClassId()
	{
		return 3;
	}

	virtual std::string getName()
	{
		return "Protecteur";
	}

	virtual std::string getGraphicsPath()
	{
		return "./assets/Protecteur/";
	}

	// Retourne la valeur du maximum de point de vie de base (sans alt�ration d'effet). C'est une caract�ristique de base de la classe.
	virtual int getBaseMaxLife()
	{
		return 75;
	}

	//Fonction � ajouter
	virtual int getBasePa()
	{
		return 6;
	}

	//Fonction � ajouter
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
		// D�cr�mentation des cooldowns :
		if (compt1 > 0)
			compt1--;
	}

	//Passif : +3 HP sur soi-m�me pour chaque auto attaque
	virtual bool doAttack1(int targetX, int targetY)
	{
		return true;
	}

	//Sort 1 : R�animation (Mana : 5 / Cibl� / DPS : 0 / Cd : usage unique)
	virtual bool doAttack2(int targetX, int targetY)
	{

		return true;
	}

	//Sort 2 : Heal (Mana : 5 / Cibl� / Heal : +20% des HP max / Cd : 3t / )
	virtual bool doAttack3(int targetX, int targetY)
	{
		return true;
	}

	//Sort 3 : Purification d'�me (Mana : 2 / Pigme (4) / DPS : 10 / Cd : 2t) Supprime 1 tour de malus chez les alli�s touch�s
	virtual bool doAttack4(int targetX, int targetY)
	{
		return true;
	}

	//Auto attaque (Mana : 0 / Corps � corps / DPS : 5 / Cd : 0t)
	virtual bool doAttack5(int targetX, int targetY)
	{
		return true;
	}

	Protecteur(tw::Environment * environment, int teamId, int currentX, int currentY)
		: BaseCharacterModel(environment, teamId, currentX, currentY)
	{
		initializeValues();
		compt1 = 99;
		compt2 = 3;
		compt3 = 2;
	}


	// M�thodes rajout�es :

	virtual std::string getClassName()
	{
		return "Protecteur";
	}

	virtual std::string getClassDescription()
	{
		return "Description protecteur ...";
	}

	virtual std::string getClassIconPath()
	{
		return "./assets/classicons/Priest.png";
	}


	//------------------------------------

	virtual std::string getSpell1Name()
	{
		return "Protecteur sort 1";
	}

	virtual std::string getSpell2Name()
	{
		return "Protecteur sort 2";
	}

	virtual std::string getSpell3Name()
	{
		return "Protecteur sort 3";
	}

	virtual std::string getSpell4Name()
	{
		return "Protecteur sort 4";
	}


	//------------------------------------
	virtual std::string getSpell1Description()
	{
		return "Protecteur, description sort 1 ...";
	}

	virtual std::string getSpell2Description()
	{
		return "Protecteur, description sort 2 ...";
	}

	virtual std::string getSpell3Description()
	{
		return "Protecteur, description sort 3 ...";
	}

	virtual std::string getSpell4Description()
	{
		return "Protecteur, description sort 4 ...";
	}


	//------------------------------------
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


	//------------------------------------
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


	//------------------------------------
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

	//------------------------------------
	virtual int getSpell1MinPO()
	{
		return 2;
	}

	virtual int getSpell2MinPO()
	{
		return 1;
	}

	virtual int getSpell3MinPO()
	{
		return 3;
	}

	virtual int getSpell4MinPO()
	{
		return 4;
	}

	//------------------------------------

	virtual int getSpell1MaxPO()
	{
		return 5;
	}

	virtual int getSpell2MaxPO()
	{
		return 3;
	}

	virtual int getSpell3MaxPO()
	{
		return 8;
	}

	virtual int getSpell4MaxPO()
	{
		return 12;
	}

	//------------------------------------

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

	//------------------------------------

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

	//------------------------------------

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

	//------------------------------------

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

