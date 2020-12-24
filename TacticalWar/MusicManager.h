#pragma once

#include <SFML/Audio.hpp>

class MusicManager
{
private:
	MusicManager();

	static MusicManager * instance;

	sf::Music menuMusic;
	sf::Music battleMusic;
	sf::SoundBuffer takeDamageSoundBuffer;
	sf::Sound takeDamageSoundInstances[4];
	int iTakeDamageInstance;

public:
	static MusicManager * getInstance();

	void setMenuMusic();
	void setBattleMusic();
	void stopMusic();
	void playTakeDamageSound();
};

