#pragma once

#include "SFML/Graphics.hpp"
#include <stack>

class State {

public:
	State(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	virtual ~State() = default;

	virtual void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) = 0; // std::optional event
	virtual void update(float dt, sf::Vector2f mouseCoords) = 0;
	virtual void render() = 0;
	bool shouldQuit() const;
	bool shouldAllowUpdateBelow() const { return allowUpdateBelow; };
	bool shouldAllowRenderBelow() const { return allowRenderBelow; };
	int statesToPop() const;
	void setQuit(bool b) { quit = b; }
	void setNumPop(int n) { numPop = n; }

protected:
	sf::RenderWindow* window = nullptr;
	std::stack<std::unique_ptr<State>>* states = nullptr;
	bool quit = false;
	bool allowUpdateBelow = false;
	bool allowRenderBelow = false;
	int numPop = 1; // number of states in stack needed to be popped
	float timeAccumulator = 0.0f;
	float frameSwitchTime = 2.0f;
};