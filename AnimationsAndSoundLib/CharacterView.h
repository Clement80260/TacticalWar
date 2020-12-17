#pragma once

#include "pch.h"
#include <AbstractCharacterView.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Pathfinder.h>
#include <deque>
#include <map>
#include <BaseCharacterModel.h>

namespace tw
{
	class CharacterView : public AbstractCharacterView<sf::Sprite*>
	{
	private:
		static std::map<std::string, sf::Texture*> * textureCache;
		static sf::Texture* getCachedTexture(std::string path);

		Orientation orientation;
		Animation animation;
		std::map<Orientation, std::map<Animation, std::vector<sf::Sprite*> > > animationsMap;
		std::map<Orientation, std::map<Animation, std::vector<sf::Sprite*> > > animationsMaskMap;

		sf::Font font;
		sf::Text pseudoTxt;
		sf::Sprite lifeBg;
		sf::Sprite paBg;
		sf::Sprite pmBg;
		sf::Text lifeTxt;
		sf::Text paTxt;
		sf::Text pmTxt;
		
		double elsetime = 0;
		
		std::vector<sf::Sprite*> loadAnimation(std::string filename, bool flip = false, bool mask = false);

	public:
		CharacterView(BaseCharacterModel * model);
		virtual ~CharacterView();
		virtual sf::Sprite * getImageToDraw();

		virtual sf::Sprite * getMaskToDraw();

		sf::Text * getPseudoText()
		{
			return &pseudoTxt;
		}

		sf::Text * getLifeText()
		{
			lifeTxt.setString(std::to_string(getModel()->getCurrentLife()) + "/" + std::to_string(getModel()->getBaseMaxLife()));
			return &lifeTxt;
		}

		sf::Text * getPaText()
		{
			paTxt.setString(std::to_string(getModel()->getCurrentPA()));
			return &paTxt;
		}

		sf::Text * getPmText()
		{
			pmTxt.setString(std::to_string(getModel()->getCurrentPM()));
			return &pmTxt;
		}

		sf::Sprite * getLifeBackground()
		{
			return &lifeBg;
		}

		sf::Sprite * getPaBackground()
		{
			return &paBg;
		}

		sf::Sprite * getPmBackground()
		{
			return &pmBg;
		}

		virtual void update(float deltatime);
		void setAnimation(Animation animation) {
			this->animation = animation;
		}
		void setOrientation(Orientation orientation)
		{
			this->orientation = orientation;
		}

		float getHeight()
		{
			float height = animationsMap[Orientation::BOTTOM_RIGHT][Animation::IDLE][0]->getGlobalBounds().height + 10;
			return height;
		}
	};
}