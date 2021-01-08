#include "SpellSlot.h"

std::map<std::string, sf::Texture> SpellSlot::textureCache;

SpellSlot::SpellSlot(tw::BaseCharacterModel * model, int attackNumber, std::string spellIconPath)
	: tgui::Picture()
{
	this->model = model;

	font.loadFromFile("./assets/font/neuropol_x_rg.ttf");

	this->attackNumber = attackNumber;
	this->getRenderer()->setTexture(*getCachedTexture("./assets/ui/slot/ActionBar_MainSlot_Background.png"));

	spellPicture = tgui::Picture::create();
	updateSpellPicture();

	spellCooldownTxt = tgui::Label::create();
	spellCooldownTxt->setInheritedFont(font);
	spellCooldownTxt->setTextSize(30);
	spellCooldownTxt->getRenderer()->setTextColor(tgui::Color::White);
	spellCooldownTxt->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	spellCooldownTxt->getRenderer()->setTextOutlineThickness(2);
	spellCooldownTxt->setText("");
}
