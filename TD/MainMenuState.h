#pragma once

#include <stack>
#include "Resource_Management.h"
#include "State.h"
#include "Button.h"
#include "MapSelectState.h"
#include "LoadGameState.h"
#include "SettingState.h"
#include "Sprite.h"
#include "SoundManager.h"

class MainMenuState : public State {

public:
	MainMenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::Text mainMenuText = sf::Text(Resource_Management::font, "TOWER DEFENSE");
	Sprite backgroundSprite = Sprite(Resource_Management::mainMenuBackgroundTexture);
	Sprite newGameButtonSprite = Sprite(Resource_Management::newGameButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40.0f });
	Sprite loadGameButtonSprite = Sprite(Resource_Management::loadGameButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f });
	Sprite settingButtonSprite = Sprite(Resource_Management::settingButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 40.0f });
	Sprite quitButtonSprite = Sprite(Resource_Management::quitButtonTexture, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 80.0f });
};

