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
	int matchPlay;
	

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
	map<int, vector<Player*>> TeamRest;
	map<int, vector<Player*>> TeamWinMatch;
	map<int, vector<Player*>> TeamLosMatch;
	TeamRest = teamIdToPlayers;
	//Nombre de tour !!
	for (int x = 0; x < equipe - 1; x++)
	{
		//Nombtre de match
			for (int i = 0; i < equipe; i++)
			{
				if (teamIdToPlayers == TeamRest) {
					
					if (TeamRest.find(indexTeam + 1) == TeamRest.end())
					{
						cout << "Tour " << indexTour << " - ";
						cout << "equipe " << TeamRest[indexTeam][0]->getTeamNumber() << " sur le banc ! ;)" << endl;
						TeamWinMatch[i+1] = TeamRest[indexTeam];
						TeamRest = TeamWinMatch;
						
					}
					else
					{
					
						cout << "Tour " << indexTour << " - ";
						cout << "equipe " << TeamRest[indexTeam][0]->getTeamNumber() << " vs " << "equipe " << TeamRest[indexTeam + 1][0]->getTeamNumber() << endl;
						TeamWinMatch[i+1] = TeamRest[indexTeam];
						TeamLosMatch[i+1] = TeamRest[indexTeam + 1];
						indexTeam += 2;
					}
					
				}
				else
				{
					cout << "coucou "<< endl;
					if(TeamRest.size() & 1)
					{
						cout << "impaire" << endl;
					}
					else
					{
						indexTeam = 1;
						for (int y = 0; y < i; y++) {
							cout << "pair" << endl;
							cout << "Tour " << indexTour << " - ";
							cout << "equipe " << TeamRest[indexTeam][0]->getTeamNumber() << " vs " << "equipe " << TeamRest[indexTeam + 1][0]->getTeamNumber() << endl;
							TeamWinMatch[i + 1] = TeamRest[indexTeam];
							TeamLosMatch[i + 1] = TeamRest[indexTeam + 1];
							indexTeam += 2;
						}
						i = equipe;
						x = equipe - 1;
					}
				}
			}
			cout << "---------------------------------" << endl;
			indexTour += 1;
	}

	return 0;
}