#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, Sprite* pauseIconSprite)
	: State(window, states),
	pauseIconSprite(pauseIconSprite) {
	allowRenderBelow = true;
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));

	pauseText.setFillColor(sf::Color::White);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(5.0f);
	pauseText.setCharacterSize(32);
	pauseText.setOrigin({ pauseText.getLocalBounds().position + pauseText.getLocalBounds().size / 2.0f });
	pauseText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 30 });


	continueGameButtonSprite.setScale({ 0.6f, 0.6f });
	saveGameButtonSprite.setScale({ 0.6f, 0.6f });
	settingButtonSprite.setScale({ 0.6f, 0.6f });
	mainMenuButtonSprite.setScale({ 0.6f, 0.6f });

	SoundManager::pauseMusic();
}

void PauseState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (pauseIconSprite->isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (continueGameButtonSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (saveGameButtonSprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<SaveGameState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (settingButtonSprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<SettingState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
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

void PauseState::update(float dt, sf::Vector2f mouseCoords) {
	pauseIconSprite->update(mouseCoords);
	continueGameButtonSprite.update(mouseCoords);
	saveGameButtonSprite.update(mouseCoords);
	settingButtonSprite.update(mouseCoords);
	mainMenuButtonSprite.update(mouseCoords);
}

void PauseState::render() {
	window->draw(dimOverlay);
	window->draw(pauseText);
	window->draw(*pauseIconSprite);
	window->draw(continueGameButtonSprite);
	window->draw(saveGameButtonSprite);
	window->draw(settingButtonSprite);
	window->draw(mainMenuButtonSprite);
}