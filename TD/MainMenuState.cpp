#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
}

void MainMenuState::handleInput(const std::optional<sf::Event>& event) {

	if (!event.has_value()) return;

	sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (newGameButton.shape.getGlobalBounds().contains(mouseCoords)) {
		newGameButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		newGameButton.shape.setPosition({ newGameButton.getInitialPosition().x,  newGameButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				states->push(std::make_unique<MapSelectState>(window, states));
				return;
			}
		}
	}
	else {
		newGameButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		newGameButton.shape.setPosition(newGameButton.getInitialPosition());
	}

	if (loadGameButton.shape.getGlobalBounds().contains(mouseCoords)) {
		loadGameButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		loadGameButton.shape.setPosition({ loadGameButton.getInitialPosition().x,  loadGameButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {

			}
		}
	}
	else {
		loadGameButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		loadGameButton.shape.setPosition(loadGameButton.getInitialPosition());
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

	if (quitButton.shape.getGlobalBounds().contains(mouseCoords)) {
		quitButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		quitButton.shape.setPosition({ quitButton.getInitialPosition().x,  quitButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				quit = true;
				numPop = 1;
				return;
			}
		}
	}
	else {
		quitButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		quitButton.shape.setPosition(quitButton.getInitialPosition());
	}
}

void MainMenuState::update(float dt) {

}

void MainMenuState::render() {
	window->draw(backgroundSprite);
	window->draw(newGameButton);
	window->draw(loadGameButton);
	window->draw(settingButton);
	window->draw(quitButton);
}

//void MainMenu::init() {
//	if (isInit) return;
//
//	if (!backgroundTexture.loadFromFile("resources/sprites/mainmenu_background.png")) {
//		std::cerr << "cannot load mainmenu_background.png file";
//		return;
//	}
//
//	backgroundSprite.setTexture(backgroundTexture);
//
//	newGameButton.setOrigin(newGameButton.getSize() / 2.0f);
//	newGameButton.setPosition(newGameButton.getPosition());
//	newGameButton.setFillColor(sf::Color::Red);
//	newGameButton.text.setString("START");
//	// text's origin = position + size
//	newGameButton.text.setOrigin({ newGameButton.text.getLocalBounds().position + newGameButton.text.getLocalBounds().size / 2.0f });
//	newGameButton.text.setPosition(newGameButton.getPosition());
//	newGameButton.text.setFillColor(sf::Color::Black);
//	newGameButton.text.setOutlineThickness(1.0f);
//	newGameButton.text.setOutlineColor(sf::Color::White);
//
//	exitButton.setOrigin(exitButton.getSize() / 2.0f);
//	exitButton.setPosition(exitButton.getPosition());
//	exitButton.setFillColor(sf::Color::Blue);
//	exitButton.text.setString("EXIT");
//	exitButton.text.setOrigin({ exitButton.text.getLocalBounds().position + exitButton.text.getLocalBounds().size / 2.0f });
//	exitButton.text.setPosition(exitButton.getPosition());
//	exitButton.text.setFillColor(sf::Color::Black);
//	exitButton.text.setOutlineThickness(1.0f);
//	exitButton.text.setOutlineColor(sf::Color::White);
//
//	isInit = true;
//}