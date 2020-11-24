#pragma once

#include <Player.h>
#include <vector>
#include "Match.h"
#include <StringUtils.h>

namespace tw
{
	class PlayerManager
	{
		static Match * testMatch;
	public:
		static std::vector<Player*> loadPlayers();
		static Match * getCurrentOrNextMatchForPlayer(Player * p);
		static std::vector<Match*> getCurrentlyPlayingMatchs();

		static void createTestMatchIfNotExists()
		{
			if (testMatch == NULL)
			{
				testMatch = new tw::Match("Tour 1 - Eq 1 VS Eq 2");
				std::vector<tw::Player*> players = loadPlayers();
				testMatch->setTeam1Players(players[0], players[1]);
				testMatch->setTeam2Players(players[2], players[3]);
			}
		}

		static void subscribeToAllMatchEvent(MatchEventListener * l);
	};
}
