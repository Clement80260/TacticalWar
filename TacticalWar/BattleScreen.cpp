#include "BattleScreen.h"
#include "TestCharacterModel.h"
#include <Pathfinder.h>
#include <ZoneAndSightCalculator.h>

using namespace tw;

BattleScreen::BattleScreen(tgui::Gui * gui)
{
	this->gui = NULL;
	this->window = NULL;
	
	gui->removeAllWidgets();
	
	renderer = new IsometricRenderer(NULL);
	environment = new Environment(15, 15, 0);
	environment->getMapData(2, 2)->setIsObstacle(true);
	environment->getMapData(1, 1)->setIsWalkable(false);

	colorator = new TWColorator(sf::Color(40, 200, 255), sf::Color(20, 100, 200));

	renderer->setColorator(colorator);
	renderer->addEventListener(this);

	activeCharacter = new TestCharacterModel(environment, 0, 0, 0);
	characters.push_back(activeCharacter);
	activeCharacter->addEventListener(this);

	font.loadFromFile("./assets/font/arial.ttf");
	FPS.setFont(font);
}

void BattleScreen::handleEvents(sf::RenderWindow * window, tgui::Gui * gui)
{	
	this->window = window;
	this->gui = gui;
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
}

void BattleScreen::render(sf::RenderWindow * window)
{
	renderer->modifyWindow(window);
	renderer->render(environment, characters, getDeltatime());
	window->draw(FPS);
}

// Renderer Event Listener
void BattleScreen::onCellClicked(int cellX, int cellY)
{
	std::cout << "Cell x=" << cellX << ", y=" << cellY << " clicked !" << std::endl;
	BaseCharacterModel * m = characters[0];
	if (!m->hasTargetPosition())
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

			std::vector<Point2D> path = Pathfinder::getInstance()->getPath(startPosition, targetPosition, environment, std::vector<Obstacle*>());
			m->setPath(path);
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
				Point2D startPosition(characters[0]->getCurrentX(), characters[0]->getCurrentY());
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
			colorator->setPathToHighlight(std::vector<Point2D>());
			lastStartPosition.setX(-1);
			lastStartPosition.setY(-1);
		}

		if (needToReprocess)
		{
			std::vector<Point2D> pathToHighlight = Pathfinder::getInstance()->getPath(lastStartPosition, lastTargetPosition, environment, std::vector<Obstacle*>());
			if (pathToHighlight.size() <= 2)
			{
				colorator->setPathToHighlight(pathToHighlight);
			}
		}
	}
	else
	{
		colorator->setPathToHighlight(std::vector<Point2D>());
		lastStartPosition.setX(-1);
		lastStartPosition.setY(-1);
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
	if (c == activeCharacter)
	{
		int x = c->getCurrentX();
		int y = c->getCurrentY();

		Point2D startPoint(x, y);

		std::vector<Point2D> zone = ZoneAndSightCalculator::getInstance()->generateZone(x, y, 1, 3, tw::TypeZoneLaunch::STAR);
		std::vector<Point2D> realZone;
		for (int i = 0; i < zone.size(); i++)
		{
			std::vector<Point2D> path = Pathfinder::getInstance()->getPath(startPoint, zone[i], environment, std::vector<Obstacle*>());
			if (path.size() <= 2)
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