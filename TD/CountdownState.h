#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "SoundManager.h"

class CountdownState : public State {

public:
	CountdownState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	sf::Text countdownText = sf::Text(Resource_Management::font, "3", 100);
	unsigned int count = 3;
};

