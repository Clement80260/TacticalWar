#include <PlayerManager.h>
#include <iostream>
#include <string>

using namespace tw;
using namespace std;

int main(int argc, char ** argv)
{
	int index = 1;
	vector<Player*> players = PlayerManager::loadPlayers();

	cout << "Liste des joueurs : \n" << endl;
	for (int i = 0; i < players.size(); i++)
	{
		cout << "Login : " << players[i]->getPseudo() << endl;
		cout << "Password : " << players[i]->getPassword() << endl;
		cout << "Team : " << players[i]->getTeamNumber() << endl << endl;
	}

	cout << "il y a " << players.size() / 2 << " equipes en jeu" << endl << endl;

	for (int i = 0; i < players.size() ; i++)
	{
		if (index == players[i]->getTeamNumber())
		{
			cout << "equipe : " << index << " -> " << players[i]->getPseudo() << " et " << players[i++]->getPseudo() << endl;
		}
		index += 1;
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