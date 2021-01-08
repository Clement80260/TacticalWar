#pragma once

#include <BaseCharacterModel.h>

namespace tw
{
	class TestCharacterModel : public BaseCharacterModel
	{
	public:
		virtual int getClassId()
		{
			return 0;
		}

		virtual std::string getGraphicsPath()
		{
			return "./assets/Warrior/";
		}

		// Retourne la valeur du maximum de point de vie de base (sans alt�ration d'effet). C'est une caract�ristique de base de la classe.
		virtual int getBaseMaxLife()
		{
			return 500;
		}

		virtual int getBaseAttack()
		{
			return 100;
		}

		virtual int getBaseDefense()
		{
			return 5;
		}

		virtual int getBasePa()
		{
			return 6;
		}

		virtual int getBasePm()
		{
			return 4;
		}

		virtual std::vector<tw::AttackDamageResult> doAttack1(int targetX, int targetY)
		{
			return std::vector<tw::AttackDamageResult>();
		}

		virtual std::vector<tw::AttackDamageResult> doAttack2(int targetX, int targetY)
		{
			return std::vector<tw::AttackDamageResult>();
		}

		virtual std::vector<tw::AttackDamageResult> doAttack3(int targetX, int targetY)
		{
			return std::vector<tw::AttackDamageResult>();
		}

		virtual std::vector<tw::AttackDamageResult> doAttack4(int targetX, int targetY)
		{
			return std::vector<tw::AttackDamageResult>();
		}

		virtual std::vector<tw::AttackDamageResult> doAttack5(int targetX, int targetY)
		{
			return std::vector<tw::AttackDamageResult>();
		}

		TestCharacterModel(Environment * environment, int teamId, int currentX, int currentY)
			: BaseCharacterModel(environment, teamId, currentX, currentY)
		{

		}


		// M�thodes rajout�es :

		virtual std::string getClassName()
		{
			return "Test";
		}

		virtual std::string getClassDescription()
		{
			return "Description test ...";
		}

		virtual std::string getClassIconPath()
		{
			return "./assets/classicons/Mage.png";
		}


		//------------------------------------

		virtual std::string getSpell1Name()
		{
			return "Test sort 1";
		}

		virtual std::string getSpell2Name()
		{
			return "Test sort 2";
		}

		virtual std::string getSpell3Name()
		{
			return "Test sort 3";
		}

		virtual std::string getSpell4Name()
		{
			return "Test sort 4";
		}


		//------------------------------------
		virtual std::string getSpell1Description()
		{
			return "Test, description sort 1 ...";
		}

		virtual std::string getSpell2Description()
		{
			return "Test, description sort 2 ...";
		}

		virtual std::string getSpell3Description()
		{
			return "Test, description sort 3 ...";
		}

		virtual std::string getSpell4Description()
		{
			return "Test, description sort 4 ...";
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
}

