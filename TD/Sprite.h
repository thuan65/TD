#pragma once

#include "SFML/Graphics.hpp"
#include "Resource_Management.h"

class MapSelectState;
class PlayState;
class PauseState;
class LoadGameState;
class SaveGameState;
class SettingState;

class Sprite : public sf::Sprite {

public:
	Sprite(const sf::Texture& texture, sf::Vector2f initialPosition = { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f });

	bool isClicked(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords);

	void update(sf::Vector2f mouseCoords);

private:
	sf::Vector2f initialPosition;


	friend class MapSelectState;
	friend class PlayState;
	friend class PauseState;
	friend class LoadGameState;
	friend class SaveGameState;
	friend class SettingState;
};


