#pragma once

#include <TGUI/TGUI.hpp>

#define BORDER_OFFSET 20
#define BORDER_OFFDIV (BORDER_OFFSET / 2)

class SpellSlot : public tgui::Picture
{
	int attackNumber;
	tgui::Picture::Ptr spellPicture;

public:
	SpellSlot(int attackNumber, std::string spellIconPath);
	tgui::Picture::Ptr getSpellPicture() {
		return spellPicture;
	}

	virtual void setPosition(const tgui::Layout2d & position)
	{
		tgui::Picture::setPosition(position);
		if(spellPicture != NULL)
			spellPicture->setPosition(position.x + BORDER_OFFDIV + 1, position.y + BORDER_OFFDIV + 1);
	}


	virtual void setSize(const tgui::Layout2d & size)
	{
		tgui::Picture::setSize(size);
		if(spellPicture != NULL)
			spellPicture->setSize(size.x - BORDER_OFFSET - 2, size.y - BORDER_OFFSET);
	}
};

