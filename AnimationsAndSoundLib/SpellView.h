#pragma once
#include "pch.h"
#include <AbstractSpellView.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Pathfinder.h>
#include <deque>
#include <map>

class SpellView : public tw::AbstractSpellView<sf::Sprite*>
{

private:
	double elsetime = 0;
	static std::map<std::string, sf::Texture*> * textureCache;
	static sf::Texture* getCachedTexture(std::string path);
	int index;
	std::vector<sf::Sprite*>  animationsMap;
	
public:
	SpellView(int x, int y);
	virtual ~SpellView();
	std::vector<sf::Sprite*> loadAnimation(std::string filename);
	virtual sf::Sprite * getImageToDraw();
	virtual void update(float deltatime);

};

