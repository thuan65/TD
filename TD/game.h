#pragma once

#include <memory>
#include <stack>
#include <vector>
#include "SFML/Graphics.hpp"
#include "State.h"
#include "MainMenuState.h"
#include "Resource_Management.h"


class game {

public:
	game();
	~game();

	void run();

	//void pushState(std::unique_ptr<State> stats);
	//void popState();
	//void changeState(std::unique_ptr<State> states);

private:
	void initResources();
	void initWindow();
	void initStates();

	void handleEvents(sf::Vector2f mouseCoords);
	void update(float dt, sf::Vector2f mouseCoords);
	void render();

private:
	sf::RenderWindow window;
	std::stack<std::unique_ptr<State>> states;
	sf::Clock dtClock;

private:
	void initMainMenuState();
};

