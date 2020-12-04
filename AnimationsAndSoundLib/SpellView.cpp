#include "pch.h"
#include "SpellView.h"
#include <iostream>
#include <string>
#include <StringUtils.h>
#include <SFML/System/FileInputStream.hpp>
std::map<std::string, sf::Texture*> * SpellView::textureCache = NULL;
sf::Texture * SpellView::getCachedTexture(std::string path)
{
	if (textureCache == NULL)
		textureCache = new std::map<std::string, sf::Texture*>();

	sf::Texture *texture;
	if (textureCache->find(path) != textureCache->end())
	{
		texture = (*textureCache)[path];
	}
	else
	{
		texture = new sf::Texture();
		texture->loadFromFile(path);
		(*textureCache)[path] = texture;
	}

	return texture;
}

SpellView::SpellView()
{



}

SpellView::~SpellView()
{
	//
}

std::vector<sf::Sprite*> SpellView::loadAnimation(std::string filename)
{

	std::vector<sf::Sprite *> anim;
	sf::Texture *testSpellTexture = getCachedTexture(filename + ".png");
	sf::FileInputStream stream;

	std::string str;
	std::vector<std::string> positionView;

	if (stream.open(filename + ".txt")) {
		int length = stream.getSize();
		char * data = new char[length + 1];
		stream.read(data, length);
		data[length] = '\0';
		std::vector<std::string> lines = StringUtils::explode(data, '\n');
		delete data;
		std::vector<std::string> info;
		
		for (int i = 0; i < lines.size(); i++) {
			if (lines[i][2] == 'x' && lines[i][3] == 'y' || lines[i][2] == 's' && lines[i][3] == 'i' && lines[i][4] == 'z' && lines[i][5] == 'e') {
				info = StringUtils::explode(lines[i], ':');
				info[0] = { 0 };
				info = StringUtils::explode(info[1], ',');
				
				for(int x = 0; x < info.size(); x++)
						positionView.push_back(info[x]);
			}
			//positionView.push_back(lines[i]);	// tant que l'on peut mettre la ligne dans "positionView"	
		}
		for (int i = 0; i < positionView.size(); i++)
			std::cout << positionView[i] << std::endl;
	}
	else
	{
		std::cout << "Echec de l'ouverture du fichier " << filename.c_str() << ".txt" << std::endl;
	}

	return std::vector<sf::Sprite*>();
}
sf::Sprite * SpellView::getImageToDraw()
{
	return nullptr;
}


void SpellView::update(float deltatime)
{
}
