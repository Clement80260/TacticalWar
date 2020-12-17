#include "pch.h"
#include "IsometricRenderer.h"
#include <CharacterView.h>
#include <SpellView.h>
#include <math.h>
#include <iostream>

using namespace tw;

IsometricRenderer::IsometricRenderer(sf::RenderWindow * window)
{
	hasFocus = true;
	forcedFocus = false;
	if (!textureGrass.loadFromFile("assets/tiles/resized/Grass_01.png")) { std::cout << "Impossible de charger Grass texture" << std::endl; }
	if (!textureWater.loadFromFile("assets/tiles/resized/Water_01.png")) { std::cout << "Impossible de charger Water texture" << std::endl; }
	if (!textureStone.loadFromFile("assets/tiles/resized/Stone_02.png")) { std::cout << "Impossible de charger Stone texture" << std::endl; }
	if (!textureTree.loadFromFile("assets/tiles/resized/Tree_01.png")) { std::cout << "Impossible de charger Tree texture" << std::endl; }

	textureGrass.setSmooth(true);
	textureWater.setSmooth(true);
	textureStone.setSmooth(true);
	textureTree.setSmooth(true);

	spriteGrass.setTexture(textureGrass);
	spriteWater.setTexture(textureWater);
	spriteStone.setTexture(textureStone);
	spriteTree.setTexture(textureTree);

	this->window = window;
	this->colorator = NULL;
}

void IsometricRenderer::manageEvents(Environment * environment, std::vector<BaseCharacterModel*> & characters)
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		// check the type of the event...
		switch (e.type)
		{
			/*
			case sf::Event::LostFocus:
				std::cout << "Lost focus" << std::endl;
				hasFocus = false;
				break;

			case sf::Event::GainedFocus:
				std::cout << "Gain focus" << std::endl;
				hasFocus = true;

				break;
			*/
			// window closed
		case sf::Event::Closed:
			window->close();
			break;

			// key pressed
		case sf::Event::KeyPressed:

			break;

		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				int x = e.mouseButton.x;
				int y = e.mouseButton.y;

				sf::Vector2f unprojected = window->mapPixelToCoords(sf::Vector2i(x, y));
				sf::Vector2i isoCoords = screenCoordinatesToIsoGridCoordinates(unprojected.x, unprojected.y);


				int cellX = isoCoords.x;
				int cellY = isoCoords.y;

				if (cellX >= 0 && cellX < environment->getWidth()
					&&
					cellY >= 0 && cellY < environment->getHeight())
				{
					if (hasFocus)
						notifyCellClicked(cellX, cellY);
				}
			}
			break;
			// we don't process other types of events
		default:
			break;
		}

		notifyEvent(&e);
	}

	// Gestion du focus :
	if (!forcedFocus)
	{
		if (window->hasFocus())
		{
			if (!hasFocus)
			{
				hasFocus = true;
				std::cout << "Gain focus" << std::endl;
			}
		}
		else
		{
			if (hasFocus)
			{
				hasFocus = false;
				std::cout << "Lost focus" << std::endl;
			}
		}
	}

	sf::Vector2i position = sf::Mouse::getPosition(*window);
	if (position.x >= 0 && position.y >= 0)
	{
		sf::Vector2f unprojected = window->mapPixelToCoords(position);
		sf::Vector2i isoCoords = screenCoordinatesToIsoGridCoordinates(unprojected.x, unprojected.y);

		int cellX = isoCoords.x;
		int cellY = isoCoords.y;

		if (cellX >= 0 && cellX < environment->getWidth()
			&&
			cellY >= 0 && cellY < environment->getHeight())
		{
			if (hasFocus)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					notifyCellMouseDown(cellX, cellY);
				}

				notifyCellHover(cellX, cellY);
			}
		}		
	}
}
	
sf::Vector2i IsometricRenderer::screenCoordinatesToIsoGridCoordinates(int screenX, int screenY)
{
	screenY -= 30;

	int calcX = floor((screenY/60.0) + (screenX/120.0));
	int calcY = ceil((screenY/60.0) - (screenX/120.0));
	//return sf::Vector2i((screenX/120 + screenY/120)*2, (screenY / 60 - screenX/60)*2);
	//return sf::Vector2i((screenX/120 - screenY/120)*64, (screenX/60+screenY/60)*64);
	return sf::Vector2i(calcX, calcY);
}

void IsometricRenderer::render(Environment* environment, std::vector<BaseCharacterModel*> & characters, std::vector<AbstractSpellView<sf::Sprite*> *> spells, float deltatime)
{
	manageEvents(environment, characters);

	sf::View view = window->getView();
	float centerX = environment->getWidth() / 2;
	float centerY = environment->getHeight() / 2;
	int viewCenterX = (centerX * 120.0 - centerY * 120.0) / 2;
	int viewCenterY = (centerY * 60.0 + centerY * 60.0) / 2;
	view.setCenter(viewCenterX + 60.0, viewCenterY + 30.0);
	window->setView(view);

	sf::Sprite * spriteToDraw;

	//spriteGrass.setPosition(-127*0.05, -309 * 0.05);
	//spriteGrass.setScale(0.05, 0.05);

	int borderX;
	int borderY;
	
	for (int i = 0; i < environment->getWidth(); i++)
	{
		for (int j = 0; j < environment->getHeight(); j++)
		{
			CellData * cell = environment->getMapData(i, j);
			if (cell->getIsObstacle())
			{
				spriteToDraw = &spriteStone;
				borderY = -590 * 0.05;
				borderX = -202 * 0.05;
			}
			else if (cell->getIsWalkable())
			{
				spriteToDraw = &spriteGrass;
				borderX = -128 * 0.05;
				borderY = -310 * 0.05;
			}
			else
			{
				borderX = -194 * 0.05;
				borderY = -260 * 0.05;
				spriteToDraw = &spriteWater;
				borderY += 10;
			}

			int isoX = (i*120 - j*120)/2; // Cordonnées
			int isoY = (i*60 + j*60)/2;

			sf::Color toApply = sf::Color::White;
			if (colorator != NULL)
			{
				toApply = colorator->getColorForCell(cell);
			}

			spriteToDraw->setColor(toApply);
			//spriteToDraw.setScale(0.05, 0.05);
			spriteToDraw->setPosition(borderX+isoX, borderY+isoY); 
			window->draw(*spriteToDraw);
		}
	}
	
	for (int i = 0; i < characters.size(); i++)
	{
		BaseCharacterModel * m = characters[i];

		if (m->isAlive())	// On dessine pas les morts !
		{
			CharacterView & v = getCharacterView(m);
			v.update(deltatime);
			sf::Sprite * s = v.getImageToDraw();
			sf::Text * pseudoTxt = v.getPseudoText();
			sf::Text * paTxt = v.getPaText();
			sf::Text * pmTxt = v.getPmText();
			sf::Text * lifeTxt = v.getLifeText();

			sf::Sprite * lifeBg = v.getLifeBackground();
			sf::Sprite * paBg = v.getPaBackground();
			sf::Sprite * pmBg = v.getPmBackground();

			int fontSize = 16;
			pseudoTxt->setCharacterSize(fontSize);
			paTxt->setCharacterSize(12);
			pmTxt->setCharacterSize(12);
			lifeTxt->setCharacterSize(12);

			int isoX = (m->getInterpolatedX() * 120 - m->getInterpolatedY() * 120) / 2;
			int isoY = (m->getInterpolatedX() * 60 + m->getInterpolatedY() * 60) / 2;

			s->setPosition(isoX + 60, isoY + 30);
			float height = v.getHeight();
			if (pseudoTxt->getString().getSize() > 0)
			{
				pseudoTxt->setPosition(isoX + 60 - (pseudoTxt->getGlobalBounds().width / 2.0), isoY + 30 - height + 5);
				pseudoTxt->setOutlineColor(sf::Color::Black);
				pseudoTxt->setOutlineThickness(1);
			}
			sf::IntRect rect = s->getTextureRect();
			bool flipped = s->getScale().x < 0;
			float scaleX = 0.4;
			float scaleY = 0.4;
			s->setScale(flipped ? -scaleX : scaleX, scaleY);
			window->draw(*s);

			if (pseudoTxt->getString().getSize() > 0)
			{
				float lifeBgY = isoY + 30 - height - pseudoTxt->getGlobalBounds().height - lifeBg->getGlobalBounds().height + 20;
				lifeBg->setPosition(isoX + 60 - (lifeBg->getGlobalBounds().width / 2.0), lifeBgY);
				lifeTxt->setPosition(isoX + 60 - (lifeTxt->getGlobalBounds().width / 2.0), lifeBgY + lifeBg->getGlobalBounds().height / 2.0 - lifeTxt->getGlobalBounds().height / 2.0 - 8);
				window->draw(*lifeBg);
				window->draw(*lifeTxt);

				paBg->setScale(0.75, 0.75);
				paBg->setPosition(isoX + 60 - (lifeBg->getGlobalBounds().width / 2.0) - (paBg->getGlobalBounds().width / 2.0) + 2, lifeBgY - 5 + (paBg->getGlobalBounds().height / 2.0));
				paTxt->setPosition(isoX + 60 - (lifeBg->getGlobalBounds().width / 2.0) - (paTxt->getGlobalBounds().width / 2.0) + 2, lifeBgY - 5 + (paBg->getGlobalBounds().height / 2.0) + (paBg->getGlobalBounds().height / 2.0) - (paTxt->getGlobalBounds().height / 2.0));
				window->draw(*paBg);
				window->draw(*paTxt);

				pmBg->setScale(0.75, 0.75);
				pmBg->setPosition(isoX + 60 + (lifeBg->getGlobalBounds().width / 2.0) - (pmBg->getGlobalBounds().width / 2.0), lifeBgY + (pmBg->getGlobalBounds().height / 2.0));
				pmTxt->setPosition(isoX + 60 + (lifeBg->getGlobalBounds().width / 2.0) - (pmTxt->getGlobalBounds().width / 2.0), lifeBgY - 5 + (pmBg->getGlobalBounds().height / 2.0) + (pmBg->getGlobalBounds().height / 2.0) - (pmTxt->getGlobalBounds().height / 2.0));
				window->draw(*pmBg);
				window->draw(*pmTxt);

				window->draw(*pseudoTxt);
			}
		}
	}
}


CharacterView & IsometricRenderer::getCharacterView(BaseCharacterModel * model)
{
	if (characterViewsCache.find(model) == characterViewsCache.end())
	{
		characterViewsCache[model] = new CharacterView(model);
	}

	return *characterViewsCache[model];
}