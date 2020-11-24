#include "pch.h"
#include "PlayerManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <deque>

using namespace std;

tw::Match * tw::PlayerManager::testMatch = NULL;

std::vector<tw::Player*> tw::PlayerManager::loadPlayers()
{
	int index = 1;
	std::vector<tw::Player*> result;

	// Vous devrez remplacer les données de test par des 
	// données chargées depuis un fichier.
	ifstream fichierTeam("./assets/equipe.txt");

	if (fichierTeam)
	{
		cout << "Ouverture reussi\n" << endl;
		string dataFile;

		fichierTeam >> dataFile;

		// Découpage des joueurs avec un '/'.
		vector<std::string> equipe = StringUtils::explode(dataFile, '/');

		for (int i = 0; i < equipe.size(); i++)
		{
			int indexName = 0;
			int indexPassword = 1;
			int indexTeam = 2;
			
			int team;

			// Découpage des noms, password et nbTeam des joueurs avec une ','.
			vector<std::string> result1 = StringUtils::explode(equipe[i], ',');

			// Conversion d'un string en int.
			team = std::atoi(result1[indexTeam].c_str());

			// Envoie des infos au serveur.
			result.push_back(new Player(result1[indexName], result1[indexPassword], team));
		}
	}
	else {
		cout << "Pas reussi\n" << endl;
	}

	//result.push_back(new Player("J1", "P1", 1));
	//result.push_back(new Player("J2", "P2", 1));
	//result.push_back(new Player("J3", "P3", 2));
	//result.push_back(new Player("J4", "P4", 2));

	return result;
}

tw::Match * tw::PlayerManager::getCurrentOrNextMatchForPlayer(tw::Player * p)
{
	createTestMatchIfNotExists();

	// TODO : Rechercher le match courant ou le prochain pour le joueur p 
	// et le retourner. Si aucun match à venir, retourner NULL.

	if (testMatch->getStatus() != FINISHED)
	{
		return testMatch;
	}

	return NULL;
}

std::vector<tw::Match*> tw::PlayerManager::getCurrentlyPlayingMatchs()
{
	std::vector<tw::Match*> result;

	createTestMatchIfNotExists();

	if (testMatch->getStatus() == MatchStatus::STARTED)
	{
		result.push_back(testMatch);
	}

	return result;
}

void tw::PlayerManager::subscribeToAllMatchEvent(MatchEventListener * l)
{
	createTestMatchIfNotExists();

	testMatch->addEventListener(l);
}