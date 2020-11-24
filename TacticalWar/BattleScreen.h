#pragma once

#include "Screen.h"
#include <IsometricRenderer.h>
#include <Environment.h>
#include <BaseCharacterModel.h>
#include "TWColorator.h"

namespace tw
{
	class BattleScreen : public Screen, RendererEventListener, CharacterEventListener
	{
	private:
		IsometricRenderer * renderer;
		Environment * environment;
		TWColorator * colorator;

		BaseCharacterModel * activeCharacter;

		std::vector<tw::BaseCharacterModel*> characters;
		sf::Font font;
		sf::Text FPS;

		sf::RenderWindow * window;
		tgui::Gui * gui;
		std::vector<Point2D> pathZone;


		Point2D lastStartPosition;
		Point2D lastTargetPosition;

	public:
		BattleScreen(tgui::Gui * gui);

		virtual void handleEvents(sf::RenderWindow * window, tgui::Gui * gui);
		virtual void update(float deltatime);
		virtual void render(sf::RenderWindow * window);



		// Renderer event listener :
		virtual void onCellClicked(int cellX, int cellY);
		virtual void onCellHover(int cellX, int cellY);
		virtual void onCellMouseDown(int cellX, int cellY);
		virtual void onEvent(void * e);

		// CharacterEventListener :
		virtual void onPositionChanged(BaseCharacterModel * c, int newPositionX, int newPositionY);
	};
}

