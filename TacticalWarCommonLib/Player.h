#pragma once
#include <string>

namespace tw
{
	class Player
	{
	private:
		std::string pseudo;
		std::string password;
		int teamNumber;
		int winnerTour;

		bool hasJoinBattle;

	public:
		Player(std::string pseudo, std::string password, int teamId);

		inline std::string getPseudo()
		{
			return pseudo;
		}

		inline std::string getPassword()
		{
			return password;
		}

		inline int getTeamNumber()
		{
			return teamNumber;
		}

		inline bool getHasJoinBattle()
		{
			return hasJoinBattle;
		}

		inline void setHasJoinBattle(bool hasJoin)
		{
			this->hasJoinBattle = hasJoin;
		}
		inline void getWinTour(bool etat)
		{
			this->winnerTour = etat;
		}
	};
}