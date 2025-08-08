#include "VictoryState.h"

VictoryState::VictoryState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	: State(window, states) {
	allowRenderBelow = true;
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));
}

void VictoryState::handleInput(const std::optional<sf::Event>& event) {

	if (!event.has_value()) return;

	sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (newGameButton.shape.getGlobalBounds().contains(mouseCoords)) {
		newGameButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		newGameButton.shape.setPosition({ newGameButton.getInitialPosition().x,  newGameButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				quit = true;
				numPop = 2;
				return;
			}
		}
	}
	else {
		newGameButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		newGameButton.shape.setPosition(newGameButton.getInitialPosition());
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

void VictoryState::update(float dt) {}

void VictoryState::render() {
	window->draw(dimOverlay);
	window->draw(victoryBackgroundSprite);
	window->draw(newGameButton);
	window->draw(mainMenuButton);
}