#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "Button.h"
#include "SaveGameState.h"
#include "Sprite.h"

class PauseState : public State {

public:
	PauseState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, Sprite* pauseIconSprite);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;

private:
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	Sprite* pauseIconSprite;

	Button resumeButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40.0f }, "Resume");
	Button saveGameButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f }, "Save Game");
	Button settingButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 40.0f }, "Settings");
	Button mainMenuButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 80.0f }, "Main Menu");
};

