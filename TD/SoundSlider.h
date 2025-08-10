#pragma once

#include "Slider.h"
#include "SoundManager.h"

class SoundSlider : public Slider {

public:
	SoundSlider(sf::Vector2f position, float initialValue = SoundManager::getSoundVolume());

	void update(sf::Vector2f mouseCoords) override;
};
