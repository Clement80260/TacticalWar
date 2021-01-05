#pragma once

#include <TGUI/TGUI.hpp>
#include <BaseCharacterModel.h>
#include <map>

#define BORDER_OFFSET 20
#define BORDER_OFFDIV (BORDER_OFFSET / 2)

class SpellSlot : public tgui::Picture
{
	int attackNumber;
	tgui::Picture::Ptr spellPicture;
	tgui::Label::Ptr spellCooldownTxt;
	tw::BaseCharacterModel * model;
	sf::Font font;

	static std::map<std::string, sf::Texture> textureCache;
	static sf::Texture * getCachedTexture(std::string path)
	{
		if (textureCache.find(path) == textureCache.end())
		{
			textureCache[path].loadFromFile(path);
			textureCache[path].setSmooth(true);
		}

		return &textureCache[path];
	}

public:
	SpellSlot(tw::BaseCharacterModel * model = NULL, int attackNumber = 0, std::string spellIconPath = "");
	tgui::Picture::Ptr getSpellPicture() {
		return spellPicture;
	}

	tgui::Label::Ptr getSpellCooldownTxt()
	{
		return spellCooldownTxt;
	}

	void setModel(tw::BaseCharacterModel * m)
	{
		this->model = m;
		updateSpellPicture();
	}

	void updateSpellPicture()
	{
		if (model != NULL)
		{
			sf::Texture * spellTexture = getCachedTexture(model->getSpellIconPath(attackNumber));
			spellPicture->getRenderer()->setTexture(*spellTexture);
			spellPicture->setSize(getSize().x - 4, getSize().y - 4);
			setPosition(getPosition());
		}
	}

	virtual void setPosition(const tgui::Layout2d & position)
	{
		tgui::Picture::setPosition(position);
		if(spellPicture != NULL)
			spellPicture->setPosition(position.x + BORDER_OFFDIV + 1, position.y + BORDER_OFFDIV + 1);

		if (spellCooldownTxt != NULL)
		{
			spellCooldownTxt->setPosition(position.x + (getSize().x / 2.0) - (spellCooldownTxt->getSize().x / 2.0), position.y + (getSize().y / 2.0) - (spellCooldownTxt->getSize().y / 2.0));
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		bool canDoAttack = model->canDoAttack(attackNumber);
		spellPicture->setEnabled(canDoAttack);
		spellCooldownTxt->setText(canDoAttack ? "" : std::to_string(model->getAttackCooldown(attackNumber)));

		if (spellCooldownTxt != NULL)
		{
			spellCooldownTxt->setPosition(getPosition().x + (getSize().x / 2.0) - (spellCooldownTxt->getSize().x / 2.0), getPosition().y + (getSize().y / 2.0) - (spellCooldownTxt->getSize().y / 2.0));
		}

		tgui::Picture::draw(target, states);
	}

	virtual void setSize(const tgui::Layout2d & size)
	{
		tgui::Picture::setSize(size);
		if(spellPicture != NULL)
			spellPicture->setSize(size.x - BORDER_OFFSET - 2, size.y - BORDER_OFFSET);

		if (spellCooldownTxt != NULL)
		{
			spellCooldownTxt->setPosition(getPosition().x + (getSize().x / 2.0) - (spellCooldownTxt->getSize().x / 2.0), getPosition().y + (getSize().y / 2.0) - (spellCooldownTxt->getSize().y / 2.0));
		}
	}
};

