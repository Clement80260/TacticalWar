#pragma once

#include "Screen.h"
#include "ServerMessageListener.h"
#include <CharacterView.h>

class ClassSelectionScreen : public tw::Screen, ServerMessageListener
{
private:
	sf::Font font;
	sf::Text title;
	sf::Text subtitle;
	sf::Text subsubtitle;

	tgui::Label::Ptr matchPanelTitle;
	tgui::ScrollablePanel::Ptr m_matchListpanel;
	//static void scrollPanel(tgui::Panel::Ptr panel, int value);
	//static int previousScrollbarValue;

	sf::Shader shader;

	tgui::Gui * gui;

	std::vector<tw::BaseCharacterModel*> classesInstances;
	tw::CharacterView * characterView;
	int indexClass;
	void setClassView();

	sf::Vector2u windowSize;
	float ellapsedTime;
	int orientation;

	bool readyToLock;

public:
	ClassSelectionScreen(tgui::Gui * gui);
	~ClassSelectionScreen();

	virtual void handleEvents(sf::RenderWindow * window, tgui::Gui * gui);
	virtual void update(float deltatime);
	virtual void render(sf::RenderWindow * window);


	virtual void onMessageReceived(std::string msg);
	virtual void onDisconnected();

	
	void setIdxClass(int classId)
	{
		if (classId < 0)
		{
			classId = classesInstances.size() - 1;
		}
		else if (classId >= classesInstances.size())
		{
			classId = 0;
		}

		this->indexClass = classId;
		setClassView();
	}

	int getIdxClass()
	{
		return indexClass;
	}
};


