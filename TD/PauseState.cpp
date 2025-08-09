#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, Sprite* pauseIconSprite)
	: State(window, states),
	pauseIconSprite(pauseIconSprite) {
	allowRenderBelow = true;
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));
}

void PauseState::handleInput(const std::optional<sf::Event>& event) {

	if (!event.has_value()) return;

	sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (pauseIconSprite->getGlobalBounds().contains(mouseCoords)) {
		pauseIconSprite->setPosition(pauseIconSprite->initialPosition + sf::Vector2f(0.0f, -2.0f));
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				quit = true;
				numPop = 1;
				return;
			}
		}
	}
	else pauseIconSprite->setPosition(pauseIconSprite->initialPosition);

	if (resumeButton.shape.getGlobalBounds().contains(mouseCoords)) {
		resumeButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		resumeButton.shape.setPosition({ resumeButton.getInitialPosition().x,  resumeButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {

				quit = true;
				numPop = 1;
				return;
			}
		}
	}
	else {
		resumeButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		resumeButton.shape.setPosition(resumeButton.getInitialPosition());
	}

	if (saveGameButton.shape.getGlobalBounds().contains(mouseCoords)) {
		saveGameButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveGameButton.shape.setPosition({ saveGameButton.getInitialPosition().x,  saveGameButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				states->push(std::make_unique<SaveGameState>(window, states));
			}
		}
	}
	else {
		saveGameButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveGameButton.shape.setPosition(saveGameButton.getInitialPosition());
	}

	if (settingButton.shape.getGlobalBounds().contains(mouseCoords)) {
		settingButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		settingButton.shape.setPosition({ settingButton.getInitialPosition().x,  settingButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {

			}
		}
	}
	else {
		settingButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		settingButton.shape.setPosition(settingButton.getInitialPosition());
	}

	if (mainMenuButton.shape.getGlobalBounds().contains(mouseCoords)) {
		mainMenuButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		mainMenuButton.shape.setPosition({ mainMenuButton.getInitialPosition().x,  mainMenuButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				quit = true;
				numPop = 3;
				return;
			}
		}
	}
	else {
		mainMenuButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		mainMenuButton.shape.setPosition(mainMenuButton.getInitialPosition());
	}
}

void PauseState::update(float dt) {}

void PauseState::render() {
	window->draw(dimOverlay);
	window->draw(*pauseIconSprite);
	window->draw(resumeButton);
	window->draw(saveGameButton);
	window->draw(settingButton);
	window->draw(mainMenuButton);
}