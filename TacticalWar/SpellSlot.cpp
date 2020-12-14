#include "SpellSlot.h"

SpellSlot::SpellSlot(int attackNumber, std::string spellIconPath)
	: tgui::Picture()
{
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
}
