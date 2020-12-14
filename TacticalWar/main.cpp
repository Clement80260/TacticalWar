
#include "IsometricRenderer.h"
#include "BattleScreen.h"
#include "LoginScreen.h"
#include "ScreenManager.h"
#include <TGUI/TGUI.hpp>

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tactical War"/*, sf::Style::Fullscreen*/);
	tgui::Gui gui{ window };
	window.setVerticalSyncEnabled(false);
	tw::ScreenManager::getInstance()->setCurrentScreen(new tw::LoginScreen(&gui));
	//tw::Screen * battle = new tw::BattleScreen(&gui);
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		tw::ScreenManager::getInstance()->getCurrentScreen()->handleEvents(&window, &gui);
		tw::ScreenManager::getInstance()->getCurrentScreen()->update(deltaClock.restart().asSeconds());
		window.clear();
		tw::ScreenManager::getInstance()->getCurrentScreen()->render(&window);
		gui.draw();
		window.display();
	}

	delete tw::ScreenManager::getInstance()->getCurrentScreen();

	return 0;
}