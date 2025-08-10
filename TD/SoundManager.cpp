#include "SoundManager.h"

const float SoundManager::cleanUpSoundsTime = 1.0f;
float SoundManager::timeAccumulator = 0.0f;

std::list<sf::Sound> SoundManager::activeSounds;
sf::Music SoundManager::music;
float SoundManager::soundVolume = std::clamp(50.0f, 0.f, 100.f);
float SoundManager::musicVolume = std::clamp(50.0f, 0.f, 100.f);
bool SoundManager::isMuted = false;

void SoundManager::playSound(sf::SoundBuffer& buffer) {
	sf::Sound& sound = activeSounds.emplace_back(buffer);
	sound.setVolume(isMuted ? 0.0f : soundVolume);
	sound.play();
}

void SoundManager::stopSound() {
	activeSounds.clear();
}

void SoundManager::playMainMenuMusic(bool loop) {
	playMusic("Data/audio/music/mario_music.wav", loop);
}

void SoundManager::playPlayMusic(bool loop) {
	playMusic("Data/audio/music/play_music.wav", loop);
}

void SoundManager::playVictoryMusic(bool loop) {
	playMusic("Data/audio/music/victory_music.wav", loop);
}

void SoundManager::playLoseMusic(bool loop) {
	playMusic("Data/audio/music/lose_music.wav", loop);
}

void SoundManager::resumeMusic() {
	music.play();
}

void SoundManager::playMusic(const std::string& filepath, bool loop) {
	music.stop();
	Resource_Management::loadMusic(music, filepath);
	music.setLooping(loop);
	music.setVolume(isMuted ? 0.0f : musicVolume);
	music.play();
}

void SoundManager::pauseMusic() {
	music.pause();
}

void SoundManager::stopMusic() {
	music.stop();
}

void SoundManager::setSoundVolume(float volume) {
	soundVolume = std::clamp(volume, 0.f, 100.f);
}

void SoundManager::setMusicVolume(float volume) {
	musicVolume = std::clamp(volume, 0.f, 100.f);
	music.setVolume(musicVolume);
}

float SoundManager::getSoundVolume() {
	return soundVolume;
}

float SoundManager::getMusicVolume() {
	return musicVolume;
}

sf::SoundSource::Status SoundManager::getMusicStatus() {
	return music.getStatus();
}

void SoundManager::muteAll() {
	isMuted = true;
	music.setVolume(0.0f);
}

void SoundManager::unmuteAll() {
	isMuted = false;
	music.setVolume(musicVolume);
}

void SoundManager::cleanUpSounds() {

	/*for (auto& s : activeSounds) {
		std::cout << "Sound status: ";
		if (s.getStatus() == sf::Sound::Status::Paused) std::cout << "paused\n";
		else if (s.getStatus() == sf::Sound::Status::Playing) std::cout << "playing\n";
		else if (s.getStatus() == sf::Sound::Status::Stopped) std::cout << "stopped\n";
	}*/

	/*activeSounds.erase(
		std::remove_if(activeSounds.begin(), activeSounds.end(),
			[](const sf::Sound& sound) {
				return sound.getStatus() == sf::SoundSource::Status::Stopped;
			}),
		activeSounds.end()
	); */

	for (auto it = activeSounds.begin(); it != activeSounds.end();) {
		if (it->getStatus() == sf::Sound::Status::Stopped) {
			it = activeSounds.erase(it); // erase returns the next iterator
		}
		else {
			++it; // only advance if nothing erased
		}
	}
}