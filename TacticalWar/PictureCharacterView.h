#pragma once

#include <TGUI/TGUI.hpp>
#include <CharacterView.h>

class PictureCharacterView : public tgui::Picture
{
private:
	tw::CharacterView * v;
public:
	PictureCharacterView(tw::CharacterView * view = NULL)
	{
		v = view;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		if (v != NULL)
		{
			v->setAnimation(tw::Animation::RUN);
			sf::Sprite * s = v->getImageToDraw();
			s->setOrigin(s->getOrigin().x, 0);
			s->setPosition(getPosition());
			target.draw(*s);
		}
	}

	void setCharacterView(tw::CharacterView * view)
	{
		v = view;
	}

	sf::FloatRect getSize()
	{
		sf::FloatRect rect;
		if (v != NULL)
		{
			rect = v->getImageToDraw()->getGlobalBounds();
		}

		return rect;
	}
};

