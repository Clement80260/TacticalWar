#include "SpellSlot.h"

SpellSlot::SpellSlot(tw::BaseCharacterModel * model, int attackNumber, std::string spellIconPath)
	: tgui::Picture()
{
	this->model = model;

	font.loadFromFile("./assets/font/neuropol_x_rg.ttf");

	this->attackNumber = attackNumber;
	sf::Texture texture;
	texture.loadFromFile("./assets/ui/slot/ActionBar_MainSlot_Background.png");
	texture.setSmooth(true);
	this->getRenderer()->setTexture(texture);

	sf::Texture spellTexture;
	spellTexture.loadFromFile(spellIconPath);
	spellTexture.setSmooth(true);
	spellPicture = tgui::Picture::create(spellTexture);
	spellPicture->setSize(getSize().x - 4, getSize().y - 4);
	setPosition(getPosition());

	spellCooldownTxt = tgui::Label::create();
	spellCooldownTxt->setInheritedFont(font);
	spellCooldownTxt->setTextSize(30);
	spellCooldownTxt->getRenderer()->setTextColor(tgui::Color::White);
	spellCooldownTxt->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	spellCooldownTxt->getRenderer()->setTextOutlineThickness(2);
	spellCooldownTxt->setText("");
}
