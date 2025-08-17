#include "LoseState.h"

LoseState::LoseState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	: State(window, states) {
	allowRenderBelow = true;
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));
	newGameButtonSprite.setScale({ 0.7f, 0.7f });
	mainMenuButtonSprite.setScale({ 0.7f, 0.7f });

	SoundManager::playLoseMusic();
}

void LoseState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

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

void LoseState::update(float dt, sf::Vector2f mouseCoords) {
	newGameButtonSprite.update(mouseCoords);
	mainMenuButtonSprite.update(mouseCoords);
}



void LoseState::render() {
	window->draw(dimOverlay);
	window->draw(loseBackgroundSprite);
	window->draw(newGameButtonSprite);
	window->draw(mainMenuButtonSprite);
}

