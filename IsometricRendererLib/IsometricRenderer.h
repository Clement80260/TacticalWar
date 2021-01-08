#pragma once

#include <AbstractRenderer.h>
#include <AbstractSpellView.h>
#include <Environment.h>
#include <BaseCharacterModel.h>
#include "CellColorator.h"

#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Shader.hpp>

namespace tw
{
	class CharacterView;

	class IsometricRenderer : public AbstractRenderer<sf::Sprite>
	{
		bool hasFocus;
		bool forcedFocus;
		
		sf::RenderWindow * window;
		CellColorator * colorator;

		std::map<BaseCharacterModel*, CharacterView*> characterViewsCache;
		CharacterView & getCharacterView(BaseCharacterModel * model);

		void manageEvents(Environment * environment, std::vector<BaseCharacterModel*> & characters);
		sf::Texture textureGrass;
		sf::Texture textureWater;
		sf::Texture textureStone;
		sf::Texture textureTree;

		sf::Sprite spriteGrass;
		sf::Sprite spriteStone;
		sf::Sprite spriteWater;
		sf::Sprite spriteTree;

		sf::Vector2i screenCoordinatesToIsoGridCoordinates(int screenX, int screenY);

		sf::Shader shader;
		sf::Shader waterShader;

		float ellapsedTime;

	public:
		IsometricRenderer(sf::RenderWindow * window);
		inline void modifyWindow(sf::RenderWindow * newWindow) { this->window = newWindow; }
		virtual void render(Environment* environment, std::vector<BaseCharacterModel*> & characters, std::vector<AbstractSpellView<sf::Sprite*> *> spells, float deltatime);

		void setColorator(CellColorator * colorator)
		{
			this->colorator = colorator;
		}

		inline void forceFocus()
		{
			forcedFocus = true;
			hasFocus = true;
			std::cout << "Force gain focus" << std::endl;
		}

		inline void forceUnfocus()
		{
			forcedFocus = true;
			hasFocus = false;
			std::cout << "Force lost focus" << std::endl;
		}

		void ellapseTime(float deltatime)
		{
			ellapsedTime += deltatime;
		}
	};
}