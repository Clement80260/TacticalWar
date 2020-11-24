#include <PlayerManager.h>
#include <iostream>
#include <string>
#include <map>

using namespace tw;
using namespace std;

int main(int argc, char ** argv)
{
	vector<Player*> players = PlayerManager::loadPlayers();
	vector<Player*> team;

	map<int, vector<Player*>> teamIdToPlayers;

	int indexTeam = 1;
	int indexMatch = 1;
	int indexTour = 1;
	int equipe = players.size() / 2;
	

	cout << "Liste des joueurs : \n" << endl;
	for (int i = 0; i < players.size(); i++)
	{
		cout << "Login : " << players[i]->getPseudo() << endl;
		cout << "Password : " << players[i]->getPassword() << endl;
		cout << "Team : " << players[i]->getTeamNumber() << endl << endl;
	}

	if (equipe / 2 > 1)
	{
		cout << "il y a " << equipe << " equipes en jeu" << endl << endl;
	}
	else
	{
		cout << "il y a " << equipe << " equipe en jeu" << endl << endl;
	}

	for (int i = 0; i < players.size() ; i+=2)
	{
		if (indexTeam == players[i]->getTeamNumber())
		{
			std::vector<Player*> joueurs;
			joueurs.push_back(players[i]);
			joueurs.push_back(players[i + 1]);
			teamIdToPlayers[indexTeam] = joueurs;

			cout << "equipe : " << indexTeam << " -> " << teamIdToPlayers[indexTeam][0]->getPseudo() << " et " << teamIdToPlayers[indexTeam][1]->getPseudo() << endl;
		}
		indexTeam += 1;
	}
	cout << "---------------------------------" << endl;

	indexTeam = 1;

	for (int i = 0; i < equipe - 1; i++)
	{
		for (int i = 0; i < equipe; i++)
		{
			// Format = Tour 1 - Eq 1 VS Eq 2
			cout << "Tour " << indexTour << " - ";
			// Faire l'arbre de tournoi automatique.
			cout << "equipe " << teamIdToPlayers[indexTeam]->getTeamNumber() << " vs " << "equipe " << teamIdToPlayers[indexTeam + 1]->getTeamNumber() << endl;
		}
		cout << "---------------------------------" << endl;
		indexTour += 1;
	}

	//Match * testMatch = PlayerManager::getCurrentOrNextMatchForPlayer(players[i]);

	//if (testMatch != NULL)
	//{
	//	cout << "match trouve" << endl;
	//}
	//else
	//{
	//	cout << "aucun match a venir" << endl;
	//}

	return 0;
}