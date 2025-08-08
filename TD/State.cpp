#include "State.h"

State::State(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	window(window),
	states(states) {
}

bool State::shouldQuit() const {
	return quit;
}

int State::statesToPop() const {
	return numPop;
}
