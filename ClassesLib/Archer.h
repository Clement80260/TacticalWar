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
		return "./assets/Archer/";
	}

	// Retourne la valeur du maximum de point de vie de base (sans alt�ration d'effet). C'est une caract�ristique de base de la classe.
	virtual int getBaseMaxLife()
	{
		return 80;
	}

	//Fonction � ajouter
	virtual int getBasePa()
	{
		return 6;
	}

	//Fonction � ajouter
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

	virtual bool canDoAttack(int spellId)
	{
		if (spellId == 1)
		{
			return compt1 <= 0;
		}
		else if (spellId == 2)
		{
			return compt2 <= 0;
		}
		else if (spellId == 3)
		{
			return compt3 <= 0;
		}

		return true;
	}

	virtual int getAttackCooldown(int spellId)
	{
		if (spellId == 1)
		{
			return compt1;
		}
		else if (spellId == 2)
		{
			return compt2;
		}
		else if (spellId == 3)
		{
			return compt3;
		}

		return 0;
	}

	virtual void setAttackCooldown(int spellId, int value)
	{
		if (spellId == 1)
		{
			compt1 = value;
		}
		else if (spellId == 2)
		{
			compt2 = value;
		}
		else if (spellId == 3)
		{
			compt3 = value;
		}
	}

	virtual void turnStart()
	{
		BaseCharacterModel::turnStart();

		// D�cr�mentation des cooldowns :
		if (compt1 > 0)
			compt1--;
	}

	//Passif : +1 de PD - fonction inutilis�e
	virtual std::vector<tw::AttackDamageResult> doAttack1(int targetX, int targetY)
	{
		return std::vector<tw::AttackDamageResult>();
	}

	//Sort 1 : Fl�che toxique : (Mana : 4 / Ligne 3x1 / DPS : 10 / Malus -3 HP / tour pendant 2 tour / Cd : 4t)
	virtual std::vector<tw::AttackDamageResult> doAttack2(int targetX, int targetY)
	{

		return std::vector<tw::AttackDamageResult>();
	}

<<<<<<< HEAD
	//Sort 2 : Fl�che repousse (Mana : 3 / Ligne 2x1 / DPS : 4 / Repousse de 2 cases / Cd : 3t)
	virtual bool doAttack3(int targetX, int targetY)
=======
	//Sort 2 : Fl�che repousse (Mana : 3 / Ligne 3x1 / DPS : 4 / Repousse de 2 cases / Cd : 3t)
	virtual std::vector<tw::AttackDamageResult> doAttack3(int targetX, int targetY)
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	{
		return std::vector<tw::AttackDamageResult>();
	}

<<<<<<< HEAD
	//Sort 3 : Tir pr�cis (Mana : 2 / Ciblable(zone 3x3) / DPS : 7 / Cd : 1t)
	virtual bool doAttack4(int targetX, int targetY)
=======
	//Sort 3 : Tir pr�cis (Mana : 2 / Ligne 4x1 / DPS : 7 / Cd : 1t)
	virtual std::vector<tw::AttackDamageResult> doAttack4(int targetX, int targetY)
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	{
		std::vector<tw::AttackDamageResult> result;
		std::vector<tw::Point2D> impactZone = getImpactZoneForSpell(4, targetX, targetY);
		std::vector<tw::BaseCharacterModel*> impactedEntities = getMapKnowledge()->getAliveCharactersInZone(impactZone);

		for (int i = 0; i < impactedEntities.size(); i++)
		{
			result.push_back(tw::AttackDamageResult(impactedEntities[i], 7));
		}

		return result;
	}

	//Auto attaque (Mana : 0 / Corps � corps / DPS : 5 / Cd : 0t)
	virtual std::vector<tw::AttackDamageResult> doAttack5(int targetX, int targetY)
	{
		return std::vector<tw::AttackDamageResult>();
	}

	Archer(tw::Environment * environment, int teamId, int currentX, int currentY, tw::IMapKnowledge * map)
		: BaseCharacterModel(environment, teamId, currentX, currentY, map)
	{
		initializeValues();
		compt1 = 4;
		compt2 = 3;
		compt3 = 1;
	}


	// M�thodes rajout�es :	TYPE DE CLASSE

	virtual std::string getClassName()
	{
		return "Archer";
	}

	virtual std::string getClassDescription()
	{
<<<<<<< HEAD
		return " Personnage distance avec des attaques de malus";
=======
		return "Lors de la bataille d'Azincourt en 1415, les archers, � l'abri de positions fortifi�es, harc�lent le corps de bataille fran�ais qui tente de r�pondre par un assaut frontal. Embourb�e et d�sorganis�e, l'arm�e fran�aise subit de lourdes pertes.";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	}

	virtual std::string getClassIconPath()
	{
		return "./assets/classicons/Chasseur.png";
	}

	virtual std::string getClassPreviewPath()
	{
		return "./assets/classpreview/Archer.png";
	}

	//------------------------------------	NOM SPELL

	virtual std::string getSpell1Name()
	{
		return "Fl�che toxique";
	}

	virtual std::string getSpell2Name()
	{
		return "Fl�che repousse";
	}

	virtual std::string getSpell3Name()
	{
		return "Tir pr�cis";
	}

	virtual std::string getSpell4Name()
	{
		return " Attaque de base";
	}


	//------------------------------------	DESCRIPTION SPELL
	virtual std::string getSpell1Description()
	{
<<<<<<< HEAD
		return "Archer, inflige 10 de d�g�ts et empoisonne sur 2 tours";
=======
		return "Archer, description sort 1 ..............................................................................................................................";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	}

	virtual std::string getSpell2Description()
	{
<<<<<<< HEAD
		return "Archer, inflige 4 de d�g�ts et repousse la cible de 2 cases";
=======
		return "Archer, description sort 2 ..............................................................................................................................";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	}

	virtual std::string getSpell3Description()
	{
<<<<<<< HEAD
		return "Archer, inflige 6 de d�g�ts et ignore les obstacles";
=======
		return "Archer, description sort 3 ..............................................................................................................................";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	}

	virtual std::string getSpell4Description()
	{
<<<<<<< HEAD
		return "Archer, inflige 5 de d�g�ts";
=======
		return "Archer, description sort 4 ..............................................................................................................................";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
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

	//------------------------------------ PORT�E MAX D'UNE SPELL
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

	//------------------------------------ PORT�E MAX D'UN SPELL

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

	//------------------------------------

	virtual std::string getSpell1AnimationPath()
	{
		return "./assets/spellsprites/claw1_red";
	}

	virtual std::string getSpell2AnimationPath()
	{
		return "./assets/spellsprites/claw1_red";
	}

	virtual std::string getSpell3AnimationPath()
	{
		return "./assets/spellsprites/ballbig1_red";
	}

	virtual std::string getSpell4AnimationPath()
	{
		return "./assets/spellsprites/ballbig1_red";
	}

	//------------------------------------

	virtual std::string getSpell1SoundPath()
	{
		return "./assets/sound/punch3.wav";
	}

	virtual std::string getSpell2SoundPath()
	{
		return "./assets/sound/punch3.wav";
	}

	virtual std::string getSpell3SoundPath()
	{
		return "./assets/sound/explosion1.wav";
	}

	virtual std::string getSpell4SoundPath()
	{
		return "./assets/sound/explosion1.wav";
	}

	//------------------------------------

	virtual tw::Animation getSpell1AttackerAnimation()
	{
		return tw::Animation::ATTACK1;
	}

	virtual tw::Animation getSpell2AttackerAnimation()
	{
		return tw::Animation::ATTACK1;
	}

	virtual tw::Animation getSpell3AttackerAnimation()
	{
		return tw::Animation::ATTACK2;
	}

	virtual tw::Animation getSpell4AttackerAnimation()
	{
		return tw::Animation::ATTACK2;
	}
	//--------------------------------------------------------------------
};

