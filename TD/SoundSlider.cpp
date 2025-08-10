#include "SoundSlider.h"

SoundSlider::SoundSlider(sf::Vector2f position, float initialValue) :
	Slider(position, initialValue) {
}

void SoundSlider::update(sf::Vector2f mouseCoords) {
	if (dragging) {
		float leftX = position.x - (barSprite.getGlobalBounds().size.x / 2.f) + (knobSprite.getGlobalBounds().size.x / 2.f);
		float rightX = position.x + (barSprite.getGlobalBounds().size.x / 2.f) - (knobSprite.getGlobalBounds().size.x / 2.f);
		float mouseX = std::clamp(mouseCoords.x, leftX, rightX);
		float percent = (mouseX - leftX) / (rightX - leftX) * 100.f;
		setValue(percent);
		SoundManager::setSoundVolume(value);
	}
}