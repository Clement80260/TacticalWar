#include "MusicManager.h"
#include <stdlib.h>
#include <SFML/Audio.hpp>

MusicManager * MusicManager::instance = NULL;

MusicManager * MusicManager::getInstance()
{
	if (instance == NULL)
		instance = new MusicManager();

	return instance;
}

MusicManager::MusicManager()
{
	menuMusic.openFromFile("./assets/music/SAM1_BGM16_sence_anxiety.wav");
	battleMusic.openFromFile("./assets/music/SAM1_BGM04_battle_battle1.wav");
	takeDamageSoundBuffer.loadFromFile("./assets/sound/McOof.wav");

	iTakeDamageInstance = 0;

	menuMusic.setLoop(true);
	battleMusic.setLoop(true);

	menuMusic.setVolume(50.0);
	battleMusic.setVolume(50.0);
}

void MusicManager::setMenuMusic()
{
	if (battleMusic.getStatus() == sf::Music::Status::Playing)
	{
		battleMusic.stop();
	}
	
	menuMusic.play();
}


void MusicManager::setBattleMusic()
{
	if (menuMusic.getStatus() == sf::Music::Status::Playing)
	{
		menuMusic.stop();
	}

	battleMusic.play();
}

void MusicManager::stopMusic()
{
	menuMusic.stop();
	battleMusic.stop();
}

void MusicManager::playTakeDamageSound()
{
	takeDamageSoundInstances[iTakeDamageInstance].setBuffer(takeDamageSoundBuffer);
	takeDamageSoundInstances[iTakeDamageInstance].play();

	iTakeDamageInstance++;
	if (iTakeDamageInstance >= 4)
		iTakeDamageInstance = 0;
}
