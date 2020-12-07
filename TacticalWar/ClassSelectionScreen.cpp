#include "ClassSelectionScreen.h"
#include "LinkToServer.h"
#include <Match.h>
#include "MatchView.h"
#include "PlayerStatusView.h"
#include "ScreenManager.h"
#include "LoginScreen.h"
#include <CharacterFactory.h>
#include "PictureCharacterView.h"



ClassSelectionScreen::ClassSelectionScreen(tgui::Gui * gui)
	: Screen()
{
	ellapsedTime = 0;
	orientation = 0;
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

	/*
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
	*/

	gui->add(PlayerStatusView::getInstance());

	LinkToServer::getInstance()->addListener(this);

	shader.loadFromFile("./assets/shaders/vertex.vert", "./assets/shaders/animatedBackground2.glsl");


	std::vector<int> classesIds = CharacterFactory::getInstance()->getClassesIds();

	
	for (int i = 0; i < classesIds.size(); i++)
	{
		classesInstances.push_back(CharacterFactory::getInstance()->constructCharacter(NULL, classesIds[i], 1, 0, 0));
	}

	indexClass = 0;
	characterView = NULL;
	

	tgui::Picture::Ptr IconMage = tgui::Picture::create();
	IconMage->setSize(70, 75);
	IconMage->setPosition(630, 250);
	
	std::shared_ptr<PictureCharacterView> classCharacterView = std::make_shared<PictureCharacterView>();
	
	
	tgui::Button::Ptr buttonSuivant = tgui::Button::create();
	buttonSuivant->setInheritedFont(font);
	buttonSuivant->setText("suivant");
	buttonSuivant->setSize(200, 100);

	tgui::Button::Ptr buttonPrecedent = tgui::Button::create();
	buttonPrecedent->setInheritedFont(font);
	buttonPrecedent->setText("precedent");
	buttonPrecedent->setSize(200, 100);

	buttonSuivant->connect("pressed", [&]() {
		int currentValue = this->getIdxClass();
		currentValue++;
		this->setIdxClass(currentValue);
	});


	buttonPrecedent->connect("pressed", [&]() {
		int currentValue = this->getIdxClass();
		currentValue--;
		this->setIdxClass(currentValue);
	});

	m_matchListpanel = tgui::ScrollablePanel::create();
	m_matchListpanel->setSize(1000, 500);
	m_matchListpanel->setPosition(550, 250);
	m_matchListpanel->setInheritedFont(font);
	m_matchListpanel->getRenderer()->setBackgroundColor(sf::Color(128, 128, 128, 128));


	gui->add(m_matchListpanel);
	gui->add(IconMage, "classIcon");
	gui->add(classCharacterView, "classCharacterView");
	
	gui->add(buttonSuivant, "buttonSuivant");
	gui->add(buttonPrecedent, "buttonPrecedent");

	setClassView();
}

void ClassSelectionScreen::setClassView()
{
	tw::BaseCharacterModel * model = classesInstances[indexClass];

	std::string pathMage = model->getClassIconPath();
	sf::Texture TextureIconClass;
	TextureIconClass.loadFromFile(pathMage);
	tgui::Picture::Ptr IconClass = gui->get<tgui::Picture>("classIcon");
	IconClass->getRenderer()->setTexture(TextureIconClass);
	IconClass->setSize(70, 75);
	IconClass->setPosition(630, 250);

	std::shared_ptr<tgui::Picture> classCharacterView = gui->get<tgui::Picture>("classCharacterView");
	std::shared_ptr<PictureCharacterView> convertedCharacterView = std::dynamic_pointer_cast<PictureCharacterView>(classCharacterView);

	if (characterView != NULL)
	{
		delete characterView;
	}

	characterView = new tw::CharacterView(model);
	characterView->setOrientation((tw::Orientation)((orientation) % 4));

	if (convertedCharacterView != NULL)
	{
		convertedCharacterView->setCharacterView(characterView);
		sf::FloatRect size = convertedCharacterView->getSize();
		convertedCharacterView->setSize(size.width, size.height);
		convertedCharacterView->setPosition(windowSize.x / 2. - convertedCharacterView->getSize().width / 2., windowSize.y / 2. - convertedCharacterView->getSize().height / 2.);
	}
}

ClassSelectionScreen::~ClassSelectionScreen()
{
	LinkToServer::getInstance()->removeListener(this);
}

void ClassSelectionScreen::handleEvents(sf::RenderWindow * window, tgui::Gui * gui)
{
	windowSize = window->getSize();

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
	ellapsedTime += deltatime;

	bool changeOrientation = false;
	if (ellapsedTime > 1)
	{
		changeOrientation = true;
		ellapsedTime = 0;
	}

	if (changeOrientation)
	{
		characterView->setOrientation((tw::Orientation)((++orientation) % 4));
	}

	if (characterView != NULL)
	{
		characterView->update(deltatime);
	}
		
}

void ClassSelectionScreen::render(sf::RenderWindow * window)
{
	shader.setUniform("time", getShaderEllapsedTime());
	shader.setUniform("resolution", sf::Glsl::Vec2(window->getSize()));

	sf::Shader::bind(&shader);
	sf::RectangleShape rect;
	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(window->getSize()));
	rect.setFillColor(sf::Color::Black);
	window->draw(rect);
	sf::Shader::bind(NULL);

	window->draw(title);
	window->draw(subtitle);

	tgui::Button::Ptr btnSuivant = gui->get<tgui::Button>("buttonSuivant");
	btnSuivant->setPosition(1250, 800);

	tgui::Button::Ptr btnPrecedent = gui->get<tgui::Button>("buttonPrecedent");
	btnPrecedent->setPosition(400, 800);

	

	// TODO envoyer une tram contenant PC + L'id de la classe ex (PC2 pour archer) lorsque le joueur verouille son choix !
	std::shared_ptr<tgui::Picture> classCharacterView = gui->get<tgui::Picture>("classCharacterView");
	std::shared_ptr<PictureCharacterView> convertedCharacterView = std::dynamic_pointer_cast<PictureCharacterView>(classCharacterView);

	if (convertedCharacterView != NULL)
	{
		convertedCharacterView->setCharacterView(characterView);
		sf::FloatRect size = convertedCharacterView->getSize();
		convertedCharacterView->setSize(size.width, size.height);
		convertedCharacterView->setPosition(windowSize.x / 2., windowSize.y / 2. - convertedCharacterView->getSize().height / 2.);
	}

	/*tgui::Picture::Ptr mage = gui->get<tgui::Picture>("mageIcon");
	mage->setVisible(false);

	tgui::Picture::Ptr archer = gui->get<tgui::Picture>("archerIcon");
	archer->setVisible(true);

	tgui::Picture::Ptr protecteur = gui->get<tgui::Picture>("protecteurIcon");
	protecteur->setVisible(false);

	tgui::Picture::Ptr barbare = gui->get<tgui::Picture>("barbareIcon");
	barbare->setVisible(false);
	*/

}

void ClassSelectionScreen::onMessageReceived(std::string msg)
{
	sf::String m = msg;

	// Le status des joueurs est géré dans PlayerStatusView (widget autonome)
}

void ClassSelectionScreen::onDisconnected()
{
	gui->removeAllWidgets();
	tw::ScreenManager::getInstance()->setCurrentScreen(new tw::LoginScreen(gui));
	delete this;
}
