#pragma once

#include "Screen.h"
#include <IsometricRenderer.h>
#include <Environment.h>
#include <BaseCharacterModel.h>
#include "TWColorator.h"
#include "LinkToServer.h"
#include <Obstacle.h>

namespace tw
{
	class BattleScreen : public Screen, RendererEventListener, CharacterEventListener, ServerMessageListener
	{
	private:
		IsometricRenderer * renderer;
		Environment * environment;
		TWColorator * colorator;

		BaseCharacterModel * activeCharacter;

		std::map<int, tw::BaseCharacterModel*> characters;
		//std::vector<tw::BaseCharacterModel*> characters;
		sf::Font font;
		sf::Text FPS;

		sf::RenderWindow * window;
		tgui::Gui * gui;
		std::vector<Point2D> pathZone;


		Point2D lastStartPosition;
		Point2D lastTargetPosition;
		void invalidatePathZone();

		std::vector<Obstacle> getDynamicObstacles();

		bool readyToValidatePosition;

		int turnToken;

		bool hasInitSpellBar;

		void calculateAndSetSpellZone();
		void clearSpellZone()
		{
			colorator->setSpellLaunchZone(std::vector<tw::Point2D>());
		}

		int selectedSpell = -1;
		void setSelectedSpell(int spellNumber)
		{
			selectedSpell = -1;
			if (spellNumber > 0 && spellNumber <= 4)
			{
				selectedSpell = spellNumber;
				calculateAndSetSpellZone();
			}

			if (selectedSpell == -1)
			{
				clearSpellZone();
			}
		}

	public:
		BattleScreen(tgui::Gui * gui, int environmentId);
		~BattleScreen();

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

		// ServerMessageListener :
		virtual void onMessageReceived(std::string msg);
		virtual void onDisconnected();
	};
}

