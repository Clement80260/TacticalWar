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

		// Retourne la valeur du maximum de point de vie de base (sans altération d'effet). C'est une caractéristique de base de la classe.
		virtual int getBaseMaxLife()
		{
			return 500;
		}

		virtual int getBasePhysicalAttack()
		{
			return 100;
		}

		virtual int getBaseMagicalAttack()
		{
			return 20;
		}

		virtual int getBasePhysicalDefense()
		{
			return 5;
		}

		virtual int getBaseMagicalDefense()
		{
			return 15;
		}

		virtual bool doAttack1(int targetX, int targetY)
		{
			return true;
		}

		virtual bool doAttack2(int targetX, int targetY)
		{
			return true;
		}

		virtual bool doAttack3(int targetX, int targetY)
		{
			return true;
		}

		virtual bool doAttack4(int targetX, int targetY)
		{
			return true;
		}

		TestCharacterModel(Environment * environment, int teamId, int currentX, int currentY)
			: BaseCharacterModel(environment, teamId, currentX, currentY)
		{

		}
	};
}

