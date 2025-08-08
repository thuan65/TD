#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "Button.h"
#include "Sprite.h"

class VictoryState : public State {

public:
	VictoryState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;

private:
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	Sprite victoryBackgroundSprite = Sprite(Resource_Management::victoryBackgroundTexture);

	Button newGameButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH * 0.25f, Resource_Management::WINDOW_HEIGHT * 0.75f }, "New Game");
	Button mainMenuButton = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH * 0.75f, Resource_Management::WINDOW_HEIGHT * 0.75f }, "Main Menu");
};

