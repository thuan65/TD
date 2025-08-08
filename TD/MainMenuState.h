#pragma once

#include <stack>
#include "Resource_Management.h"
#include "State.h"
#include "Button.h"
#include "MapSelectState.h"
#include "Sprite.h"

class MainMenuState : public State {

public:
	MainMenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;

private:
	Sprite backgroundSprite = Sprite(Resource_Management::mainMenuBackgroundTexture);
	Button newGameButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40.0f }, "New Game");
	Button loadGameButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f }, "Load Game");
	Button settingButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 40.0f }, "Settings");
	Button quitButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 80.0f }, "Quit");
};

