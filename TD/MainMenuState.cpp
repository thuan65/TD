#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {

	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setOutlineColor(sf::Color::Black);
	mainMenuText.setOutlineThickness(5.0f);
	mainMenuText.setCharacterSize(40);
	mainMenuText.setOrigin({ mainMenuText.getLocalBounds().position + mainMenuText.getLocalBounds().size / 2.0f });
	mainMenuText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 50 });

	newGameButtonSprite.setScale({ 0.6f, 0.6f });
	loadGameButtonSprite.setScale({ 0.6f, 0.6f });
	settingButtonSprite.setScale({ 0.6f, 0.6f });
	quitButtonSprite.setScale({ 0.6f, 0.6f });

	SoundManager::playMainMenuMusic();
}

void MainMenuState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (newGameButtonSprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<MapSelectState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (loadGameButtonSprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<LoadGameState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (settingButtonSprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<SettingState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (quitButtonSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::stopMusic();
		return;
	}
}

void MainMenuState::update(float dt, sf::Vector2f mouseCoords) {

	newGameButtonSprite.update(mouseCoords);
	loadGameButtonSprite.update(mouseCoords);
	settingButtonSprite.update(mouseCoords);
	quitButtonSprite.update(mouseCoords);

	if (SoundManager::getMusicStatus() == sf::Music::SoundSource::Status::Stopped) {
		SoundManager::playMainMenuMusic();
	}
}

void MainMenuState::render() {
	window->draw(backgroundSprite);
	window->draw(mainMenuText);
	window->draw(newGameButtonSprite);
	window->draw(loadGameButtonSprite);
	window->draw(settingButtonSprite);
	window->draw(quitButtonSprite);
}