#pragma once

#include <TGUI/TGUI.hpp>
#include <BaseCharacterModel.h>

#define BORDER_OFFSET 20
#define BORDER_OFFDIV (BORDER_OFFSET / 2)

class SpellSlot : public tgui::Picture
{
	int attackNumber;
	tgui::Picture::Ptr spellPicture;
	tgui::Label::Ptr spellCooldownTxt;
	tw::BaseCharacterModel * model;
	sf::Font font;

public:
	SpellSlot(tw::BaseCharacterModel * model, int attackNumber, std::string spellIconPath);
	tgui::Picture::Ptr getSpellPicture() {
		return spellPicture;
	}

	tgui::Label::Ptr getSpellCooldownTxt()
	{
		return spellCooldownTxt;
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

