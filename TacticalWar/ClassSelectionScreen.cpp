#include "ClassSelectionScreen.h"
#include "LinkToServer.h"
#include <Match.h>
#include "MatchView.h"
#include "PlayerStatusView.h"
//#include <../ClassesLib/CharacterFactory.h>

ClassSelectionScreen::ClassSelectionScreen(tgui::Gui * gui)
	: Screen()
{
	using namespace std;

	float formFontSize = 16;
	float formElementWidth = 200;
	float formElementHeight = 25;

	this->gui = gui;
	gui->removeAllWidgets();
	font.loadFromFile("./assets/font/neuropol_x_rg.ttf");

	title.setFont(font);
	title.setCharacterSize(128);
	title.setString("Tactical War");
	title.setFillColor(sf::Color::White);
	//title.setStyle(sf::Text::Bold);
	title.setOutlineColor(sf::Color(255, 215, 0));
	title.setOutlineThickness(3);

	subtitle.setFont(font);
	subtitle.setCharacterSize(32);
	subtitle.setString("Sélection de la classe");
	subtitle.setFillColor(sf::Color::Red);
	subtitle.setOutlineColor(sf::Color(255, 215, 0));
	subtitle.setOutlineThickness(1.5);

	tgui::Button::Ptr buttonSuivant = tgui::Button::create();
	buttonSuivant->setInheritedFont(font);
	buttonSuivant->setTextSize(formFontSize);
	buttonSuivant->setText("suivant");
	buttonSuivant->setSize(100, 100);

	gui->add(buttonSuivant, "buttonSuivant");

	tgui::Button::Ptr buttonPrecedent = tgui::Button::create();
	buttonPrecedent->setInheritedFont(font);
	buttonPrecedent->setTextSize(formFontSize);
	buttonPrecedent->setText("precedent");
	buttonPrecedent->setSize(100, 100);

	gui->add(buttonPrecedent, "buttonPrecedent");

	tw::BaseCharacterModel * model = CharacterFactory::getInstance()->constructCharacter(NULL, 1, 1, 0, 0);
	std::string path = model->getClassIconPath();

	sf::Texture texture;
	if (!texture.loadFromFile(path));

	tgui::Picture::Ptr IconTest = tgui::Picture::create(texture);
	gui->add(IconTest);


	matchPanelTitle = tgui::Label::create();
	matchPanelTitle->setInheritedFont(font);
	matchPanelTitle->setTextSize(20);
	matchPanelTitle->setText("Match(s) en cours :");

	m_matchListpanel = tgui::ScrollablePanel::create();
	m_matchListpanel->setSize(1000, 600);
	m_matchListpanel->setInheritedFont(font);
	m_matchListpanel->getRenderer()->setBackgroundColor(sf::Color(128, 128, 128));

	gui->add(matchPanelTitle);
	gui->add(m_matchListpanel);
	

	gui->add(PlayerStatusView::getInstance());

	LinkToServer::getInstance()->addListener(this);
}

ClassSelectionScreen::~ClassSelectionScreen()
{
	LinkToServer::getInstance()->removeListener(this);
}

void ClassSelectionScreen::handleEvents(sf::RenderWindow * window, tgui::Gui * gui)
{
	title.setPosition(window->getSize().x / 2 - title.getLocalBounds().width / 2, 10);
	subtitle.setPosition(window->getSize().x / 2 - subtitle.getLocalBounds().width / 2, 10 + 128 + 10);
	//matchPanelTitle->setPosition(window->getSize().x / 2.0 - m_matchListpanel->getSize().x / 2.0, 270);
	//m_matchListpanel->setPosition(window->getSize().x / 2.0 - m_matchListpanel->getSize().x / 2.0, 300);

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::Resized)
		{
			int sizeX = event.size.width;
			int sizeY = event.size.height;
			sf::View view = window->getView();
			view.setSize(event.size.width, event.size.height);
			window->setView(view);
		}

		gui->handleEvent(event);
	}
}

void ClassSelectionScreen::update(float deltatime)
{
	Screen::update(deltatime);
	LinkToServer::getInstance()->UpdateReceivedData();
}

void ClassSelectionScreen::render(sf::RenderWindow * window)
{

	window->draw(title);
	window->draw(subtitle);

	tgui::Button::Ptr btn1 = gui->get<tgui::Button>("buttonSuivant");
	btn1->setPosition(1250, 400);

	tgui::Button::Ptr btn2 = gui->get<tgui::Button>("buttonPrecedent");
	btn2->setPosition(400, 400);	

	


}

void ClassSelectionScreen::onMessageReceived(std::string msg)
{
	sf::String m = msg;

	// Le status des joueurs est géré dans PlayerStatusView (widget autonome)
}