#pragma once

#include <BaseCharacterModel.h>
#include <Environment.h>

class Guerrier : public tw::BaseCharacterModel
{
private:

	int tour = 1;
	int compt1, compt2, compt3;

public:
	virtual int getClassId()
	{
		return 4;
	}

	virtual std::string getName()
	{
		return "Guerrier";
	}

	virtual std::string getGraphicsPath()
	{
		return "./assets/Warrior/";
	}

	// Retourne la valeur du maximum de point de vie de base (sans alt�ration d'effet). C'est une caract�ristique de base de la classe.
	virtual int getBaseMaxLife()
	{
		return 95;
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

	//Passif : -50% d'HP -> +15% de d�g�ts ; -35% d'HP -> +25% de d�g�ts
	virtual std::vector<tw::AttackDamageResult> doAttack1(int targetX, int targetY)
	{
		return std::vector<tw::AttackDamageResult>();
	}

	//Sort 1 : Charge (Mana : 3 / Sort en ligne 4x1 / DPS : 10 / Cd : 3t)
	virtual std::vector<tw::AttackDamageResult> doAttack2(int targetX, int targetY)
	{
		return std::vector<tw::AttackDamageResult>();
	}

	//Sort 2 : Rempart (Mana : 4 / Zone 3x3 autour + Soi-m�me / DPS : 0 / Cd : 4t) : -30% de d�g�ts re�us sur soi-m�me / -15% de d�g�ts re�us sur les alli�s
	virtual std::vector<tw::AttackDamageResult> doAttack3(int targetX, int targetY)
	{
		return std::vector<tw::AttackDamageResult>();
	}

<<<<<<< HEAD
	//Sort 3 : Frappe bouclier (Mana : 2 / Zone autour du joueur / DPS : 8 / Cd : 2t)
	virtual bool doAttack4(int targetX, int targetY)
=======
	//Sort 3 : Frappe bouclier (Mana : 2 / Zone 3x3 autour du joueur / DPS : 8 / Cd : 2t)
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

	Guerrier(tw::Environment * environment, int teamId, int currentX, int currentY, tw::IMapKnowledge * map)
		: BaseCharacterModel(environment, teamId, currentX, currentY, map)
	{
		initializeValues();
		compt1 = 3;
		compt2 = 4;
		compt3 = 1;
	}

	// M�thodes rajout�es : 

	virtual std::string getClassName()
	{
		return "Guerrier";
	}

	virtual std::string getClassDescription()
	{
<<<<<<< HEAD
		return " Personnage de combat rapproch� avec des boost de r�sistance et d'attaque";
=======
		return "Un guerrier est une personne sp�cialis�e dans le combat ou la guerre, en particulier dans le contexte d'une soci�t� de culture guerri�re tribale ou bas�e sur le clan qui reconna�t une classe ou une caste de guerriers distincte.";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	}

	virtual std::string getClassIconPath()
	{
		return "./assets/classicons/Barbare.png";
	}

	virtual std::string getClassPreviewPath()
	{
		return "./assets/classpreview/Guerrier.png";
	}


	//------------------------------------

	virtual std::string getSpell1Name()
	{
		return "Charge";
	}

	virtual std::string getSpell2Name()
	{
		return "Rempart";
	}

	virtual std::string getSpell3Name()
	{
		return "Frappe bouclier";
	}

	virtual std::string getSpell4Name()
	{
		return "Attaque de base�";
	}


	//------------------------------------
	virtual std::string getSpell1Description()
	{
<<<<<<< HEAD
		return "Charge pour infliger";
=======
		return "Guerrier, description sort 1 .................................................................................................................................";
>>>>>>> 2f55d20d4e3657a28375df34d6e14836e5c0b17d
	}

	virtual std::string getSpell2Description()
	{
		return "Guerrier, description sort 2 .................................................................................................................................";
	}

	virtual std::string getSpell3Description()
	{
		return "Guerrier, description sort 3 ..............................................................................................................................";
	}

	virtual std::string getSpell4Description()
	{
		return "Guerrier, description sort 4 ..............................................................................................................................";
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
		return 3;
	}

	virtual int getSpell2ManaCost()
	{
		return 4;
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
		return 1;
	}

	virtual int getSpell2MinPO()
	{
		return 0;
	}

	virtual int getSpell3MinPO()
	{
		return 1;
	}

	virtual int getSpell4MinPO()
	{
		return 1;
	}

	//------------------------------------

	virtual int getSpell1MaxPO()
	{
		return 4;
	}

	virtual int getSpell2MaxPO()
	{
		return 3;
	}

	virtual int getSpell3MaxPO()
	{
		return 1;
	}

	virtual int getSpell4MaxPO()
	{
		return 1;
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

