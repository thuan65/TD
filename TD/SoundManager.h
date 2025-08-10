#pragma once

#include "Resource_Management.h"
#include <list>
#include <algorithm>

class SoundManager {

public:
	static void playSound(sf::SoundBuffer& buffer);
	static void stopSound();

	static void playMainMenuMusic(bool loop = true);
	static void playPlayMusic(bool loop = true);
	static void playVictoryMusic(bool loop = false);
	static void playLoseMusic(bool loop = false);

	static void resumeMusic();
	static void pauseMusic();
	static void stopMusic();

	static void setSoundVolume(float volume);
	static void setMusicVolume(float volume);

	static float getSoundVolume();
	static float getMusicVolume();

	static sf::SoundSource::Status getMusicStatus();

	static void muteAll();
	static void unmuteAll();

	static void cleanUpSounds();

public:
	static const float cleanUpSoundsTime;
	static float timeAccumulator;

private:
	SoundManager() = default;

	static std::list<sf::Sound> activeSounds;
	static sf::Music music;

	static float soundVolume;
	static float musicVolume;
	static bool isMuted;

	static void playMusic(const std::string& filepath, bool loop = true);
};