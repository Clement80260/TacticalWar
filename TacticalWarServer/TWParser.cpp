#include "TWParser.h"
#include <iostream>

#include "TcpServer.h"
#include <StringUtils.h>
#include <PlayerManager.h>
#include <Match.h>
#include <CharacterFactory.h>
#include <EnvironmentManager.h>

TWParser::TWParser()
{
	loadEnvironments();
	
	players = tw::PlayerManager::loadPlayers();
	std::cout << players.size() << " joueurs charges :" << std::endl;

	// Construct player pseudo to player data map :
	for (int i = 0; i < players.size(); i++)
	{
		std::cout << players[i]->getPseudo().c_str() << " (equipe " << players[i]->getTeamNumber() << ")" << std::endl;
		playersMap[players[i]->getPseudo()] = players[i];
		teamIdToPlayerList[players[i]->getTeamNumber()].push_back(players[i]);
	}

	tw::PlayerManager::subscribeToAllMatchEvent(this);
}

void TWParser::loadEnvironments()
{
	std::vector<int> envIds = tw::EnvironmentManager::getInstance()->getAlreadyExistingIds();
	for (int i = 0; i < envIds.size(); i++)
	{
		tw::Environment * e = tw::EnvironmentManager::getInstance()->loadEnvironment(envIds[i]);
		if (e != NULL)
		{
			environments.push_back(e);
		}
	}
}

TWParser::~TWParser()
{
}

bool TWParser::hasCompleteMessage(ClientState * client)
{
	bool result = false;
	std::deque<unsigned char> & buffer = client->getBuffer();

	for (int i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] == '\n')
		{
			result = true;
			break;
		}
	}

	return result;
}

std::string TWParser::extractCompleteMessageFromBuffer(ClientState * client)
{
	std::string result;
	int i = 0;
	std::deque<unsigned char> & buffer = client->getBuffer();
	
	while (buffer.front() != '\n')
	{
		result += buffer.front();
		buffer.pop_front();
	}

	buffer.pop_front();	// To remove the '\n' from the buffer.

	return result;
}

void TWParser::parse(ClientState * client, std::vector<unsigned char> & receivedPacket)
{
	bool spectatorMode = false;
	std::deque<unsigned char> & buffer = client->getBuffer();

	for (int i = 0; i < receivedPacket.size(); i++)
	{
		unsigned char c = receivedPacket[i];
		buffer.push_back(c);
	}

	// Implémentation du protocole :
	if (hasCompleteMessage(client))
	{
		std::string toParse = extractCompleteMessageFromBuffer(client);

		// Connexion d'un client (login joueur ou spectateur)
		if (StringUtils::startsWith(toParse, "HG"))
		{
			std::string payload = toParse.substr(2);

			bool wrongIds = false;

			// Connexion joueur :
			if (payload.length() > 0)
			{
				std::vector<std::string> data = StringUtils::explode(payload, ';');
				if (data.size() >= 2)
				{
					std::string pseudo = data[0];
					std::string password = data[1];

					if (pseudo == "admin" && password == "admin")
					{
						client->setIsAdmin(true);
						TcpServer<TWParser, ClientState>::Send(client, (char*)"AD\n", 3);
					}
					else if (playersMap.find(pseudo) != playersMap.end())
					{
						tw::Player * p = playersMap[pseudo];

						if (password == p->getPassword())
						{
							std::cout << "Connexion du joueur " << pseudo.c_str() << std::endl;

							// Si compte déjà utilisé : déconnexion du client précédent
							if (connectedPlayerMap.find(p) != connectedPlayerMap.end())
							{
								std::cout << "Compte deja utilise, kick du client precedent" << std::endl;
								// Kick :
								kick(connectedPlayerMap[p]);
							}

							client->setPseudo(pseudo);
							connectedPlayerMap[p] = client;

							tw::Match * match = tw::PlayerManager::getCurrentOrNextMatchForPlayer(p);
							if (match->getStatus() == tw::MatchStatus::STARTED)
							{
								// Retour en jeu (reconnexion en combat)
								Battle * b = (Battle*)match->getBattlePayload();
								// TODO : Notify that the player is back.
								TcpServer<TWParser, ClientState>::Send(client, (char*)"HG\n", 3);
								TcpServer<TWParser, ClientState>::Send(client, (char*)"CA\n", 3);
								TcpServer<TWParser, ClientState>::Send(client, (char*)"CS\n", 3);
							}
							else
							{
								// Envoi vers l'écran de choix de classe
								TcpServer<TWParser, ClientState>::Send(client, (char*)"HC\n", 3);
								p->setHasJoinBattle(true);
								notifyMatchConnectedPlayerChanged(match);
								//match->setMatchStatus(tw::MatchStatus::STARTED);	// For test purpose
							}
						}
						else
							wrongIds = true;
					}
					else wrongIds = true;
				}
				else if (data.size() >= 1)
				{
					wrongIds = true;
				}
				else
					spectatorMode = true;
			}
			else // Connexion spectateur
				spectatorMode = true;

			if (wrongIds)
			{
				TcpServer<TWParser, ClientState>::Send(client, (char*)"HK\n", 3);	// Kick
			}
			else if (spectatorMode)
			{
				spectatorModeClientDiffusionList.push_back(client);
				TcpServer<TWParser, ClientState>::Send(client, (char*)"HS\n", 3);
				
				notifyPlayingMatchList();
			}
		}
		// Demande de la liste des matchs en cours :
		else if (StringUtils::startsWith(toParse, "ML"))
		{
			notifyPlayingMatchList(client);
		}
		// Demande de la liste des équipes :
		else if (StringUtils::startsWith(toParse, "TL"))
		{
			notifyTeamList(client);
		}
		// Demande la création d'un match :
		else if (StringUtils::startsWith(toParse, "CM"))
		{
			// Seul un administrateur est autorisé à réaliser cette opération :
			if (client->isAdmin())
			{
				std::string payload = toParse.substr(2);

				std::vector<std::string> matchData = StringUtils::explode(payload, ';');

				std::string name = matchData[0];
				int team1 = std::atoi(matchData[1].c_str());
				int team2 = std::atoi(matchData[2].c_str());

				tw::Match * m = new tw::Match(name);

				std::vector<tw::Player*> teamA = teamIdToPlayerList[team1];
				std::vector<tw::Player*> teamB = teamIdToPlayerList[team2];

				m->setTeam1Players(teamA[0], teamA[1]);
				m->setTeam2Players(teamB[0], teamB[1]);

				m->addEventListener(this);
				tw::PlayerManager::addMatch(m);
				notifyMatchCreated(m);
			}
		}
	}
}

void TWParser::notifyMatchCreated(tw::Match * m)
{
	notifyPlayingMatchList();
	
	std::vector<ClientState *> diffusionList;
	for (int i = 0; i < m->getTeam1().size(); i++)
	{
		tw::Player * p = m->getTeam1()[i];
		// TODO : Terminer la notification des clients déjà connectés (entrée en mode choix de classe)
		//p->
		//m->getTeam1()[]
	}
}

void TWParser::notifyTeamList(ClientState * c)
{
	std::string data = "TL";
	int i = 0;
	for (std::map<int, std::vector<tw::Player*>>::iterator it = teamIdToPlayerList.begin(); it != teamIdToPlayerList.end(); it++)
	{
		if (i > 0)
		{
			data += ";";
		}

		int teamId = (*it).first;
		std::vector<tw::Player*> team = (*it).second;

		data += std::to_string(teamId) + ",";
		
		for (int j = 0; j < team.size(); j++)
		{
			if (j > 0)
				data += "^";

			data += team[j]->getPseudo();
		}

		i++;
	}

	data += "\n";

	TcpServer<TWParser, ClientState>::Send(c, (char*)data.c_str(), data.length());
}

void TWParser::notifyPlayingMatchList(ClientState * c)
{
	// Envoi de la liste des matchs en cours
	std::vector<tw::Match*> playingMatch = tw::PlayerManager::getCurrentlyPlayingMatchs();
	
	std::string matchData = "";

	for (int i = 0; i < playingMatch.size(); i++)
	{
		if (i != 0)
			matchData += ';';
		matchData += playingMatch[i]->serialize();
	}

	matchData = "ML" + matchData + '\n';

	// Si envoi à un client spécifique, envoi uniquement au client passé en paramètre
	if (c != NULL)
	{
		TcpServer<TWParser, ClientState>::Send(c, (char*)matchData.c_str(), matchData.size());
	}
	// Envoi à tout le monde (mise à jour de la liste suite à une modif)
	else
	{
		for (int i = 0; i < spectatorModeClientDiffusionList.size(); i++)
		{
			TcpServer<TWParser, ClientState>::Send(spectatorModeClientDiffusionList[i], (char*)matchData.c_str(), matchData.size());
		}
	}
}

void TWParser::parse(SOCKET sock, unsigned char * buf, int length)
{
	Parser<ClientState>::parse(sock, buf, length);
}

void TWParser::kick(ClientState * client)
{
	// TODO : Notify disconnection to other clients (if in battle)
	notifyKick(client);
}

void TWParser::onClientConnected(ClientState * client)
{
	std::cout << "Client connecte" << std::endl;
	Parser<ClientState>::onClientConnected(client);
}

void TWParser::onClientDisconnected(SOCKET sock)
{
	Parser<ClientState>::onClientDisconnected(sock);
}

void TWParser::onClientDisconnected(ClientState * client)
{
	// If spectator, clear it from the spectator diffusion list :
	std::vector<ClientState*>::iterator it = std::find(spectatorModeClientDiffusionList.begin(), spectatorModeClientDiffusionList.end(), client);
	if (it != spectatorModeClientDiffusionList.end())
	{
		spectatorModeClientDiffusionList.erase(it);
	}
	
	// Clear connected player map :
	if (client->getPseudo().length() > 0 && playersMap.find(client->getPseudo()) != playersMap.end())
	{
		tw::Player * p = playersMap[client->getPseudo()];
		
		p->setHasJoinBattle(false);

		if (playerToBattleMap.find(p) != playerToBattleMap.end())
		{
			std::cout << "Notify battle that connection is lost with " << p->getPseudo().c_str() << std::endl;
			
			// TODO : Notify battle that the connection with the player is lost
			//playerToBattleMap[p]->connectionLostWith(p);
		}

		connectedPlayerMap.erase(p);
		notifyMatchConnectedPlayerChanged(tw::PlayerManager::getCurrentOrNextMatchForPlayer(p));
		std::cout << "Client " << p->getPseudo().c_str() << " disconnected ..." << std::endl;
	}
	Parser<ClientState>::onClientDisconnected(client);	
}


void TWParser::onMatchStatusChanged(tw::Match * match, tw::MatchStatus oldStatus, tw::MatchStatus newStatus)
{
	// Notify spectator mode clients
	notifyPlayingMatchList();
}


void TWParser::notifyMatchConnectedPlayerChanged(tw::Match * match)
{
	if (match != NULL)
	{
		std::vector<tw::Player*> team1 = match->getTeam1();
		std::vector<tw::Player*> team2 = match->getTeam2();

		std::string playerStatus;
		std::vector<tw::Player*> diffusionList;

		for (int i = 0; i < team1.size(); i++)
		{
			if (i > 0)
				playerStatus += ";";
			tw::Player * p = team1[i];
			playerStatus += p->getPseudo() + "," + std::to_string((p->getHasJoinBattle() ? 1 : 0));

			if (p->getHasJoinBattle())
				diffusionList.push_back(p);
		}

		playerStatus += ";";

		for (int i = 0; i < team2.size(); i++)
		{
			if (i > 0)
				playerStatus += ";";
			tw::Player * p = team2[i];
			playerStatus += p->getPseudo() + "," + std::to_string((p->getHasJoinBattle() ? 1 : 0));

			if (p->getHasJoinBattle())
				diffusionList.push_back(p);
		}

		playerStatus = "PS" + playerStatus + "\n";

		// Notify online players :
		for (int i = 0; i < diffusionList.size(); i++)
		{
			ClientState * c = connectedPlayerMap[diffusionList[i]];
			if (c != NULL)
			{
				TcpServer<TWParser, ClientState>::Send(c, (char*)playerStatus.c_str(), playerStatus.size());
			}
		}
	}
}