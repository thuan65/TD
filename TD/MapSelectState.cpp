#include "MapSelectState.h"

MapSelectState::MapSelectState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {

	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));

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
	goBackArrowSprite.setScale({ 0.4f, 0.4f });
}

void MapSelectState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (goBackArrowSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (map1Sprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<PlayState>(window, states, MapID::Map1));
		states->push(std::make_unique<LoadingBeforePlayState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (map2Sprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<PlayState>(window, states, MapID::Map2));
		states->push(std::make_unique<LoadingBeforePlayState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (map3Sprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<PlayState>(window, states, MapID::Map3));
		states->push(std::make_unique<LoadingBeforePlayState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (map4Sprite.isClicked(event, mouseCoords)) {
		states->push(std::make_unique<PlayState>(window, states, MapID::Map4));
		states->push(std::make_unique<LoadingBeforePlayState>(window, states));
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}
}

void MapSelectState::update(float dt, sf::Vector2f mouseCoords) {

	goBackArrowSprite.update(mouseCoords);
	map1Sprite.update(mouseCoords);
	map2Sprite.update(mouseCoords);
	map3Sprite.update(mouseCoords);
	map4Sprite.update(mouseCoords);

	if (SoundManager::getMusicStatus() != sf::Music::SoundSource::Status::Playing) {
		SoundManager::playMainMenuMusic();
	}
}

void MapSelectState::render() {
	window->draw(backgroundSprite);
	window->draw(dimOverlay);
	window->draw(mapSelectText);
	window->draw(map1Sprite);
	window->draw(map2Sprite);
	window->draw(map3Sprite);
	window->draw(map4Sprite);
	window->draw(goBackArrowSprite);
}
