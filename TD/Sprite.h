#pragma once

#include "SFML/Graphics.hpp"
#include "Resource_Management.h"

class MapSelectState;
class PlayState;
class PauseState;

class Sprite : public sf::Sprite {

public:
	Sprite(const sf::Texture& texture, sf::Vector2f initialPosition = { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f }) :
		sf::Sprite(texture),
		initialPosition(initialPosition) {
		this->setOrigin({ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });
		this->setPosition(initialPosition);
	}

public:
	sf::Vector2f initialPosition;
private:

	friend class MapSelectState;
	friend class PlayState;
	friend class PauseState;
};

