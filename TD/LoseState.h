#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "SoundManager.h"
#include "Button.h"
#include "Sprite.h"

class LoseState : public State {

public:
	LoseState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	Sprite loseBackgroundSprite = Sprite(Resource_Management::loseBackgroundTexture);
	Sprite newGameButtonSprite = Sprite(Resource_Management::newGameButtonTexture, { Resource_Management::WINDOW_WIDTH * 0.25f, Resource_Management::WINDOW_HEIGHT * 0.75f });
	Sprite mainMenuButtonSprite = Sprite(Resource_Management::mainMenuButtonTexture, { Resource_Management::WINDOW_WIDTH * 0.75f, Resource_Management::WINDOW_HEIGHT * 0.75f });
};