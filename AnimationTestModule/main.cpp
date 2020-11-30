

#include <Environment.h>
#include <BaseCharacterModel.h>
#include <vector>
#include <IsometricRenderer.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <AnimationManager.h>
#include <Mage.h>

#include "ScreenCallbackTest.h"
#include <LaunchSpellAction.h>

using namespace tw;

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SightTestModule test module");
	sf::Clock deltaClock;

	IsometricRenderer renderer(&window);
	Environment environment(20, 20, 0);
	std::vector<BaseCharacterModel*> characters;

	ScreenCallbackTest * screen = new ScreenCallbackTest(&environment);
	characters.push_back(screen->getCharacter(1)->getCharacter());
	characters.push_back(screen->getCharacter(2)->getCharacter());

	environment.getMapData(5, 7)->setIsObstacle(true);
	environment.getMapData(6, 7)->setIsWalkable(false);
	environment.getMapData(7, 7)->setIsObstacle(true);
	environment.getMapData(8, 7)->setIsWalkable(false);


	environment.getMapData(10, 10)->setIsWalkable(false);
	
	environment.getMapData(12, 12)->setIsWalkable(false);
	environment.getMapData(13, 13)->setIsObstacle(true);

	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));
	AnimationManager::getInstance()->addAnimation(new LaunchSpellAction(screen, 1, 11, 11));

	while (window.isOpen())
	{
		float deltatime = deltaClock.restart().asSeconds();

		AnimationManager::getInstance()->update(deltatime);

		for (int i = 0; i < characters.size(); i++)
			characters[i]->update(deltatime);

		/*
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		*/

		window.clear();
		renderer.render(&environment, characters, deltatime);
		window.display();
	}

	return 0;
}