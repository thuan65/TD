#include "VictoryState.h"

VictoryState::VictoryState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	: State(window, states) {
	allowRenderBelow = true;
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));
	SoundManager::playVictoryMusic();
	newGameButtonSprite.setScale({ 0.7f, 0.7f });
	mainMenuButtonSprite.setScale({ 0.7f, 0.7f });
}

void VictoryState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (newGameButtonSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 2;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		SoundManager::stopMusic();
		return;
	}

	if (mainMenuButtonSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 3;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		SoundManager::stopMusic();
		return;
	}
}

void VictoryState::update(float dt, sf::Vector2f mouseCoords) {}

void VictoryState::render() {
	window->draw(dimOverlay);
	window->draw(victoryBackgroundSprite);
	window->draw(newGameButtonSprite);
	window->draw(mainMenuButtonSprite);
}