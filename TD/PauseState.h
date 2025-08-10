#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "SoundManager.h"
#include "Button.h"
#include "Sprite.h"
#include "SaveGameState.h"
#include "SettingState.h"

class PauseState : public State {

public:
	PauseState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, Sprite* pauseIconSprite);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	sf::Text pauseText = sf::Text(Resource_Management::font, "PAUSE");
	Sprite* pauseIconSprite;

	Sprite continueGameButtonSprite = Sprite(Resource_Management::continueGameButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40.0f });
	Sprite saveGameButtonSprite = Sprite(Resource_Management::saveGameButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f });
	Sprite settingButtonSprite = Sprite(Resource_Management::settingButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 40.0f });
	Sprite mainMenuButtonSprite = Sprite(Resource_Management::mainMenuButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 80.0f });
};