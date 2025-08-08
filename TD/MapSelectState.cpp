#include "MapSelectState.h"

MapSelectState::MapSelectState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {

	mapSelectText.setFillColor(sf::Color::White);
	mapSelectText.setOutlineColor(sf::Color::Black);
	mapSelectText.setOutlineThickness(5.0f);
	mapSelectText.setCharacterSize(32);
	mapSelectText.setOrigin({ mapSelectText.getLocalBounds().position + mapSelectText.getLocalBounds().size / 2.0f });
	mapSelectText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 30 });

	map1Sprite.setScale({ (1.0f / 3.0f), (1.0f / 3.0f) });
	map2Sprite.setScale({ (1.0f / 3.0f), (1.0f / 3.0f) });
	map3Sprite.setScale({ (1.0f / 3.0f), (1.0f / 3.0f) });
	map4Sprite.setScale({ (1.0f / 3.0f), (1.0f / 3.0f) });
	goBackArrowSprite.setScale({ 0.2f, 0.2f });
	goBackArrowSprite.rotate(sf::degrees(180));
}

void MapSelectState::handleInput(const std::optional<sf::Event>& event) {

	if (!event.has_value()) return;

	sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (goBackArrowSprite.getGlobalBounds().contains(mouseCoords)) {
		goBackArrowSprite.setPosition(goBackArrowSprite.initialPosition + sf::Vector2f(0.0f, -2.0f));
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				quit = true;
				numPop = 1;
				return;
			}
		}
	}
	else goBackArrowSprite.setPosition(goBackArrowSprite.initialPosition);

	if (map1Sprite.getGlobalBounds().contains(mouseCoords)) {
		map1Sprite.setPosition(map1Sprite.initialPosition + sf::Vector2f(0.0f, -2.0f));
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				states->push(std::make_unique<PlayState>(window, states, MapID::Map1));
				return;
			}
		}
	}
	else map1Sprite.setPosition(map1Sprite.initialPosition);

	if (map2Sprite.getGlobalBounds().contains(mouseCoords)) {
		map2Sprite.setPosition(map2Sprite.initialPosition + sf::Vector2f(0.0f, -2.0f));
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				states->push(std::make_unique<PlayState>(window, states, MapID::Map2));
				return;
			}
		}
	}
	else map2Sprite.setPosition(map2Sprite.initialPosition);

	if (map3Sprite.getGlobalBounds().contains(mouseCoords)) {
		map3Sprite.setPosition(map3Sprite.initialPosition + sf::Vector2f(0.0f, -2.0f));
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				states->push(std::make_unique<PlayState>(window, states, MapID::Map3));
				return;
			}
		}
	}
	else map3Sprite.setPosition(map3Sprite.initialPosition);

	if (map4Sprite.getGlobalBounds().contains(mouseCoords)) {
		map4Sprite.setPosition(map4Sprite.initialPosition + sf::Vector2f(0.0f, -2.0f));
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				states->push(std::make_unique<PlayState>(window, states, MapID::Map4));
				return;
			}
		}
	}
	else map4Sprite.setPosition(map4Sprite.initialPosition);
}

void MapSelectState::update(float dt) {

}

void MapSelectState::render() {
	window->draw(backgroundSprite);
	window->draw(mapSelectText);
	window->draw(map1Sprite);
	window->draw(map2Sprite);
	window->draw(map3Sprite);
	window->draw(map4Sprite);
	window->draw(goBackArrowSprite);
}
