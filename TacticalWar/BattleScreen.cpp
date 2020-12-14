#include "BattleScreen.h"
#include "TestCharacterModel.h"
#include <Pathfinder.h>
#include <ZoneAndSightCalculator.h>
#include <EnvironmentManager.h>
#include <TypeZoneLaunch.h>
#include "ScreenManager.h"
#include "LoginScreen.h"
#include <StringUtils.h>
#include <CharacterFactory.h>
#include "MusicManager.h"
#include "PlayerStatusView.h"
#include "SpellSlot.h"


using namespace tw;


BattleScreen::BattleScreen(tgui::Gui * gui, int environmentId)
{
	hasInitSpellBar = false;
	turnToken = -1;
	readyToValidatePosition = false;
	this->gui = NULL;
	this->window = NULL;
	
	gui->removeAllWidgets();
	
	renderer = new IsometricRenderer(NULL);
	//environment = new Environment(15, 15, 0);
	//environment->getMapData(2, 2)->setIsObstacle(true);
	//environment->getMapData(1, 1)->setIsWalkable(false);
	environment = EnvironmentManager::getInstance()->loadEnvironment(environmentId);

	
	colorator = new TWColorator(sf::Color(40, 200, 255), sf::Color(20, 100, 200));

	renderer->setColorator(colorator);
	renderer->addEventListener(this);

	activeCharacter = NULL;

	font.loadFromFile("./assets/font/neuropol_x_rg.ttf");
	FPS.setFont(font);


	tgui::Button::Ptr readyButton = tgui::Button::create();
	readyButton->setInheritedFont(font);
	readyButton->setText("Valider position");
	readyButton->setSize(200, 100);
	readyButton->setVisible(false);
	readyButton->connect("pressed", [&]() {
		if (activeCharacter != NULL && !activeCharacter->isPlayerReady() && !readyToValidatePosition)
		{
			readyToValidatePosition = true;
		}
	});

	gui->add(readyButton, "readyButton");

	gui->add(PlayerStatusView::getInstance());

	LinkToServer::getInstance()->addListener(this);
	MusicManager::getInstance()->setBattleMusic();
}

BattleScreen::~BattleScreen()
{
	LinkToServer::getInstance()->removeListener(this);
}

void BattleScreen::handleEvents(sf::RenderWindow * window, tgui::Gui * gui)
{	
	this->window = window;
	this->gui = gui;

	tgui::Button::Ptr readyButton = gui->get<tgui::Button>("readyButton");
	readyButton->setPosition(window->getSize().x / 2. - readyButton->getSize().x / 2., window->getSize().y - readyButton->getSize().y - 20);
	if (activeCharacter != NULL)
	{
		readyButton->setVisible(!activeCharacter->isPlayerReady());

		if(!hasInitSpellBar)
		{
			std::shared_ptr<SpellSlot> spellSlot1 = std::make_shared<SpellSlot>(1, activeCharacter->getSpell1IconPath());
			gui->add(spellSlot1, "spellSlot1");
			gui->add(spellSlot1->getSpellPicture(), "spellSlot1Picture");
			spellSlot1->setSize(tgui::Layout2d(100, 100));
			spellSlot1->setPosition(tgui::Layout2d(150, window->getSize().y - 110));
			spellSlot1->getSpellPicture()->connect("Clicked", [&]() {
				setSelectedSpell(1);
			});

			std::shared_ptr<SpellSlot> spellSlot2 = std::make_shared<SpellSlot>(2, activeCharacter->getSpell2IconPath());
			gui->add(spellSlot2, "spellSlot2");
			gui->add(spellSlot2->getSpellPicture(), "spellSlot2Picture");
			spellSlot2->setSize(tgui::Layout2d(100, 100));
			spellSlot2->setPosition(tgui::Layout2d(150 + 110, window->getSize().y - 110));
			spellSlot2->getSpellPicture()->connect("Clicked", [&]() {
				setSelectedSpell(2);
			});

			std::shared_ptr<SpellSlot> spellSlot3 = std::make_shared<SpellSlot>(3, activeCharacter->getSpell3IconPath());
			gui->add(spellSlot3, "spellSlot3");
			gui->add(spellSlot3->getSpellPicture(), "spellSlot3Picture");
			spellSlot3->setSize(tgui::Layout2d(100, 100));
			spellSlot3->setPosition(tgui::Layout2d(150 + 220, window->getSize().y - 110));
			spellSlot3->getSpellPicture()->connect("Clicked", [&]() {
				setSelectedSpell(3);
			});

			std::shared_ptr<SpellSlot> spellSlot4 = std::make_shared<SpellSlot>(4, activeCharacter->getSpell4IconPath());
			gui->add(spellSlot4, "spellSlot4");
			gui->add(spellSlot4->getSpellPicture(), "spellSlot4Picture");
			spellSlot4->setSize(tgui::Layout2d(100, 100));
			spellSlot4->setPosition(tgui::Layout2d(150 + 330, window->getSize().y - 110));
			spellSlot4->getSpellPicture()->connect("Clicked", [&]() {
				setSelectedSpell(4);
			});

			hasInitSpellBar = true;
		}
	}
}

void tw::BattleScreen::calculateAndSetSpellZone()
{
	int spellMinPO = -1;
	int spellMaxPO = -1;
	TypeZoneLaunch zoneType = TypeZoneLaunch::NORMAL;
	
	if (activeCharacter != NULL)
	{
		switch (selectedSpell)
		{
		case 1:
			spellMinPO = activeCharacter->getSpell1MinPO();
			spellMaxPO = activeCharacter->getSpell1MaxPO();
			zoneType = activeCharacter->getSpell1LaunchZoneType();
			break;

		case 2:
			spellMinPO = activeCharacter->getSpell2MinPO();
			spellMaxPO = activeCharacter->getSpell2MaxPO();
			zoneType = activeCharacter->getSpell2LaunchZoneType();
			break;

		case 3:
			spellMinPO = activeCharacter->getSpell3MinPO();
			spellMaxPO = activeCharacter->getSpell3MaxPO();
			zoneType = activeCharacter->getSpell3LaunchZoneType();
			break;

		case 4:
			spellMinPO = activeCharacter->getSpell4MinPO();
			spellMaxPO = activeCharacter->getSpell4MaxPO();
			zoneType = activeCharacter->getSpell4LaunchZoneType();
			break;
		}
	}

	if (activeCharacter != NULL && selectedSpell != -1)
	{
		std::vector<Point2D> targetZone = ZoneAndSightCalculator::getInstance()->generateZone(
			activeCharacter->getCurrentX(),
			activeCharacter->getCurrentY(),
			spellMinPO,
			spellMaxPO,
			zoneType);

		std::vector<Obstacle> obstacles;
		std::vector<Obstacle> environmentObstacles = environment->getObstacles();
		std::vector<Obstacle> dynamicsObstacles = getDynamicObstacles();
		obstacles.insert(obstacles.end(), environmentObstacles.begin(), environmentObstacles.end());
		obstacles.insert(obstacles.end(), dynamicsObstacles.begin(), dynamicsObstacles.end());

		std::vector<Point2D> targettable = ZoneAndSightCalculator::getInstance()->processLineOfSight(
			activeCharacter->getCurrentX(),
			activeCharacter->getCurrentY(),
			targetZone,
			obstacles
		);

		colorator->setSpellLaunchZone(targettable);
	}
}

void BattleScreen::update(float deltatime)
{
	Screen::update(deltatime);

	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->update(deltatime);
	}

	double fps = 1.0 / deltatime;
	FPS.setString(std::to_string((int)fps));
	FPS.setFillColor(sf::Color::Red);
	FPS.setPosition(10, 10);

	if (readyToValidatePosition)
	{
		if (activeCharacter != NULL && !activeCharacter->isPlayerReady())
		{
			LinkToServer::getInstance()->Send("Cs");
		}
	}


	LinkToServer::getInstance()->UpdateReceivedData();
}

void BattleScreen::render(sf::RenderWindow * window)
{
	renderer->modifyWindow(window);
	std::vector<BaseCharacterModel*> aliveCharacters;
	
	for (std::map<int, BaseCharacterModel*>::iterator it = characters.begin(); it != characters.end(); it++)
	{
		aliveCharacters.push_back((*it).second);
	}

	renderer->render(environment, aliveCharacters, std::vector<AbstractSpellView<sf::Sprite*>*>(), getDeltatime());
	window->draw(FPS);
}

void BattleScreen::invalidatePathZone()
{
	colorator->setPathToHighlight(std::vector<Point2D>());
	lastStartPosition.setX(-1);
	lastStartPosition.setY(-1);
}

std::vector<Obstacle> tw::BattleScreen::getDynamicObstacles()
{
	std::vector<Obstacle> obstacles;

	for (auto it = characters.begin(); it != characters.end(); it++)
	{
		if(activeCharacter != (*it).second)
			obstacles.push_back(Obstacle((*it).second));
	}

	return obstacles;
}

// Renderer Event Listener
void BattleScreen::onCellClicked(int cellX, int cellY)
{
	std::cout << "Cell x=" << cellX << ", y=" << cellY << " clicked !" << std::endl;
	BaseCharacterModel * m = activeCharacter;
	if (colorator->getBattleState() == BattleState::BATTLE_PHASE_ACTIVE_PLAYER_TURN /* Temporaire : */|| colorator->getBattleState() == BattleState::BATTLE_PHASE)
	{
		std::vector<tw::Point2D> spellZone = colorator->getSpellLaunchZone();

		// Ciblage :
		if(spellZone.size() > 0)
		{
			bool isInSpellZone = false;

			for (int i = 0; i < spellZone.size(); i++)
			{
				if (spellZone[i].getX() == cellX && spellZone[i].getY() == cellY)
				{
					isInSpellZone = true;
					break;
				}
			}

			if (!isInSpellZone)
			{
				setSelectedSpell(-1);
			}
			else
			{
				// TODO : Launch spell ...
			}
		}
		// Déplacement :
		else if (m != NULL && !m->hasTargetPosition())
		{
			bool isInPathZone = false;
			for (int i = 0; i < pathZone.size(); i++)
			{
				if (pathZone[i].getX() == cellX && pathZone[i].getY() == cellY)
				{
					isInPathZone = true;
					break;
				}
			}

			if (isInPathZone)
			{
				Point2D startPosition(m->getCurrentX(), m->getCurrentY());
				Point2D targetPosition(cellX, cellY);

				std::vector<Point2D> path = Pathfinder::getInstance()->getPath(startPosition, targetPosition, environment, getDynamicObstacles());
				m->setPath(path);
			}
		}
	}
	else if (colorator->getBattleState() == BattleState::PREPARATION_PHASE)
	{
		if (m != NULL && !m->isPlayerReady())
		{
			CellData * cell = environment->getMapData(cellX, cellY);
			if (cell->getTeamStartPointNumber() == m->getTeamId())
			{
				LinkToServer::getInstance()->Send("CP" + std::to_string(cellX) + ";" + std::to_string(cellY));
			}
		}
	}
}

void BattleScreen::onCellHover(int cellX, int cellY)
{
	CellData * cell = environment->getMapData(cellX, cellY);
	if (!cell->getIsObstacle() && cell->getIsWalkable())
	{
		bool needToReprocess = false;
		bool isInPathZone = false;
		for (int i = 0; i < pathZone.size(); i++)
		{
			if (pathZone[i].getX() == cellX && pathZone[i].getY() == cellY)
			{
				Point2D startPosition(activeCharacter->getCurrentX(), activeCharacter->getCurrentY());
				Point2D targetPosition(cellX, cellY);

				if (startPosition != lastStartPosition || targetPosition != lastTargetPosition)
				{
					lastStartPosition = startPosition;
					lastTargetPosition = targetPosition;
					needToReprocess = true;
				}

				isInPathZone = true;
				break;
			}
		}

		if (!isInPathZone)
		{
			invalidatePathZone();
		}

		if (needToReprocess)
		{
			std::vector<Point2D> pathToHighlight = Pathfinder::getInstance()->getPath(lastStartPosition, lastTargetPosition, environment, getDynamicObstacles());
			if (pathToHighlight.size() <= 2)
			{
				colorator->setPathToHighlight(pathToHighlight);
			}
		}
	}
	else
	{
		invalidatePathZone();
	}
}

void BattleScreen::onCellMouseDown(int cellX, int cellY)
{

}

void BattleScreen::onEvent(void * e)
{
	if (e != NULL)
	{
		sf::Event * event = (sf::Event*)e;

		if (event->type == sf::Event::Resized)
		{
			if (window != NULL)
			{
				int sizeX = event->size.width;
				int sizeY = event->size.height;
				sf::View view = window->getView();
				view.setSize(event->size.width, event->size.height);
				window->setView(view);
			}
		}
		else if (event->type == sf::Event::KeyPressed)
		{
			if (event->key.code == sf::Keyboard::Num1)
			{
				setSelectedSpell(1);
			}
			else if (event->key.code == sf::Keyboard::Num2)
			{
				setSelectedSpell(2);
			}
			else if (event->key.code == sf::Keyboard::Num3)
			{
				setSelectedSpell(3);
			}
			else if (event->key.code == sf::Keyboard::Num4)
			{
				setSelectedSpell(4);
			}
			else if (event->key.code == sf::Keyboard::Escape)
			{
				setSelectedSpell(-1);
			}
		}

		if(gui != NULL)
			gui->handleEvent(*event);
	}
}
//----------------------------------------------------------



//----------------------------------------------------------
// CharacterEventListener :
//----------------------------------------------------------
void BattleScreen::onPositionChanged(BaseCharacterModel * c, int newPositionX, int newPositionY)
{
	sf::Clock test;
	// Refresh the position :
	if (c == activeCharacter && activeCharacter != NULL)
	{
		int x = c->getCurrentX();
		int y = c->getCurrentY();

		Point2D startPoint(x, y);

		std::vector<Point2D> zone = ZoneAndSightCalculator::getInstance()->generateZone(x, y, 1, 4, TypeZoneLaunch::STAR);
		std::vector<Point2D> realZone;
		for (int i = 0; i < zone.size(); i++)
		{
			std::vector<Point2D> path = Pathfinder::getInstance()->getPath(startPoint, zone[i], environment, getDynamicObstacles());
			if (path.size() > 0 && path.size() <= 2)
			{
				realZone.push_back(zone[i]);
			}
		}

		pathZone = realZone;
		colorator->setPathZone(pathZone);
	}
	sf::Time ellapsed = test.restart();
	std::cout << "Time to reprocess path zone = " << ellapsed.asMilliseconds() << "ms" << std::endl;
}

//----------------------------------------------------------



//----------------------------------------------------------
// ServerMessageListener :
//----------------------------------------------------------
void BattleScreen::onMessageReceived(std::string msg)
{
	sf::String str = msg;
	
	if (str.substring(0, 2) == "CA")	// Add character
	{
		std::string data = str.substring(2).toAnsiString();
		std::vector<std::string> splitedData = StringUtils::explode(data, ';');
		int characterId = std::atoi(splitedData[0].c_str());
		int classId = std::atoi(splitedData[1].c_str());
		int teamId = std::atoi(splitedData[2].c_str());
		int currentX = std::atoi(splitedData[3].c_str());
		int currentY = std::atoi(splitedData[4].c_str());

		BaseCharacterModel * c = CharacterFactory::getInstance()->constructCharacter(environment, classId, teamId, currentX, currentY);
		characters[characterId] = c;
		c->addEventListener(this);

		// To reprocess the path zone with new obstacles :
		if (activeCharacter != NULL)
		{
			onPositionChanged(activeCharacter, activeCharacter->getCurrentX(), activeCharacter->getCurrentY());
		}
	}
	else if (str.substring(0, 2) == "CS")	// Set active character
	{
		int characterId = std::atoi(str.substring(2).toAnsiString().c_str());
		activeCharacter = characters[characterId];
		onPositionChanged(activeCharacter, activeCharacter->getCurrentX(), activeCharacter->getCurrentY());
	}
	else if (str.substring(0, 2) == "BS")	// Set battle state
	{
		int state = std::atoi(str.substring(2).toAnsiString().c_str());
		BattleState battleState = (BattleState)state;
		colorator->setBattleState(battleState);

		if (battleState == BattleState::BATTLE_PHASE)
		{
			if (activeCharacter != NULL)
			{
				onPositionChanged(activeCharacter, activeCharacter->getCurrentX(), activeCharacter->getCurrentY());
			}
		}
	}
	else if (str.substring(0, 2) == "Cs")	// Player ready status
	{
		std::string data = str.substring(2);
		std::vector<std::string> splited = StringUtils::explode(data, ';');
		int playerId = std::atoi(splited[0].c_str());
		int status = std::atoi(splited[1].c_str());

		characters[playerId]->setReadyStatus(status == 1);
	}
	else if (str.substring(0, 2) == "CP")	// Update character position 
	{
		std::string data = str.substring(2);
		std::vector<std::string> splited = StringUtils::explode(data, ';');
		int playerId = std::atoi(splited[0].c_str());
		int cellX = std::atoi(splited[1].c_str());
		int cellY = std::atoi(splited[2].c_str());

		characters[playerId]->setCurrentX(cellX);
		characters[playerId]->setCurrentY(cellY);
	}
	else if (str.substring(0, 2) == "Ct")	// Changement de tour
	{
		std::string data = str.substring(2);
		int playerId = std::atoi(data.c_str());
		turnToken = playerId;
		characters[playerId]->turnStart();
	}
}

void tw::BattleScreen::onDisconnected()
{
	gui->removeAllWidgets();
	tw::ScreenManager::getInstance()->setCurrentScreen(new tw::LoginScreen(gui));
	delete this;
}

//----------------------------------------------------------