#pragma once

#include "Slider.h"
#include "SoundManager.h"

class MusicSlider : public Slider {

public:
	MusicSlider(sf::Vector2f position, float initialValue = SoundManager::getMusicVolume());

	void update(sf::Vector2f mouseCoords) override;
};
