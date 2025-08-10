#pragma once

#include "SFML/Graphics.hpp"
#include "Sprite.h"
#include "Resource_Management.h"
#include <algorithm>

class Slider : public sf::Drawable {

public:
	Slider(sf::Vector2f position, float initialValue = 50.f);

	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords);
	virtual void update(sf::Vector2f mouseCoords) {}

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const override;
	void setKnobPosition(float v);
	void setValue(float v);
	float getValue() const;

protected:
	//sf::Vector2f size;
	sf::Vector2f position;
	float value; // could be volume or brightness value
	bool dragging = false;
	Sprite barSprite = Sprite(Resource_Management::barVolumeTexture);
	Sprite knobSprite = Sprite(Resource_Management::knobVolumeTexture);

	//sf::RectangleShape bar;
	//sf::CircleShape knob;
};