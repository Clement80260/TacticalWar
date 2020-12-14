

#include <Environment.h>
#include <BaseCharacterModel.h>
#include <vector>
#include <IsometricRenderer.h>
#include <SFML/Graphics.hpp>
#include "TestColorator.h"
#include <iostream>

using namespace tw;

int main(int argc, char** argv)
{
	int *textureLoad = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Isometric renderer test module");
	sf::Clock deltaClock;
	
	IsometricRenderer renderer(&window);
	Environment environment(20, 20, 0);
	std::vector<BaseCharacterModel*> characters;


	
	environment.getMapData(0, 0)->setIsObstacle(true);
	environment.getMapData(0, 1)->setIsWalkable(false);
	environment.getMapData(0, 2)->setIsObstacle(true);
	environment.getMapData(0, 3)->setIsWalkable(false);

	environment.getMapData(1, 0)->setIsWalkable(false);
	environment.getMapData(1, 1)->setIsObstacle(true);
	environment.getMapData(1, 2)->setIsWalkable(false);
	environment.getMapData(1, 3)->setIsObstacle(true);

	environment.getMapData(2, 0)->setIsObstacle(true);
	environment.getMapData(2, 1)->setIsWalkable(false);
	environment.getMapData(2, 2)->setIsObstacle(true);
	environment.getMapData(2, 3)->setIsWalkable(false);


	environment.getMapData(3, 0)->setIsWalkable(false);
	environment.getMapData(3, 1)->setIsObstacle(true);
	environment.getMapData(3, 2)->setIsWalkable(false);
	environment.getMapData(3, 3)->setIsObstacle(true);

	

	renderer.setColorator(new TestColorator());
	
	while (window.isOpen())
	{
		float deltatime = deltaClock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		renderer.render(&environment, characters, std::vector<AbstractSpellView<sf::Sprite*>>(), deltatime);
		window.display();
	}
	
	return 0;
}