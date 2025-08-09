#include "LoadGameState.h"

LoadGameState::LoadGameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	loadGameText.setFillColor(sf::Color::White);
	loadGameText.setOutlineColor(sf::Color::Black);
	loadGameText.setOutlineThickness(5.0f);
	loadGameText.setCharacterSize(32);
	loadGameText.setOrigin({ loadGameText.getLocalBounds().position + loadGameText.getLocalBounds().size / 2.0f });
	loadGameText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 30 });

	slotEmptyText.setFillColor(sf::Color::Red);
	slotEmptyText.setOutlineColor(sf::Color::Black);
	slotEmptyText.setOutlineThickness(2.0f);
	slotEmptyText.setCharacterSize(24);
	slotEmptyText.setOrigin({ slotEmptyText.getLocalBounds().position + slotEmptyText.getLocalBounds().size / 2.0f });
	slotEmptyText.setPosition({saveSlot1Button.getInitialPosition().x + saveSlot1Button.shape.getSize().x - 20, saveSlot1Button.getInitialPosition().y});

	goBackArrowSprite.setScale({ 0.2f, 0.2f });
	goBackArrowSprite.rotate(sf::degrees(180));

	checkSaveSlots();
}

void LoadGameState::handleInput(const std::optional<sf::Event>& event) {

	if (!event.has_value()) return;

	sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	shouldDrawEmptySaveSlot1 = shouldDrawEmptySaveSlot2 = shouldDrawEmptySaveSlot3 = shouldDrawEmptySaveSlot4 = false;

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

	if (saveSlot1Button.shape.getGlobalBounds().contains(mouseCoords)) {
		saveSlot1Button.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveSlot1Button.shape.setPosition({ saveSlot1Button.getInitialPosition().x,  saveSlot1Button.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				if (!isEmptySaveSlot1) {
					// load from file to game
					loadGameFromFile(saveFileName1);
					return;
				}
				else {
					shouldDrawEmptySaveSlot1 = true;
					slotEmptyText.setPosition({ saveSlot1Button.getInitialPosition().x + saveSlot1Button.shape.getSize().x - 20, saveSlot1Button.getInitialPosition().y });
				}
			}
		}
	}
	else {
		saveSlot1Button.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveSlot1Button.shape.setPosition(saveSlot1Button.getInitialPosition());
	}

	if (saveSlot2Button.shape.getGlobalBounds().contains(mouseCoords)) {
		saveSlot2Button.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveSlot2Button.shape.setPosition({ saveSlot2Button.getInitialPosition().x,  saveSlot2Button.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				if (!isEmptySaveSlot2) {
					// load from file to game
					loadGameFromFile(saveFileName2);
					return;

				}
				else {
					shouldDrawEmptySaveSlot2 = true;
					slotEmptyText.setPosition({ saveSlot2Button.getInitialPosition().x + saveSlot2Button.shape.getSize().x - 20, saveSlot2Button.getInitialPosition().y });
				}
			}
		}
	}
	else {
		saveSlot2Button.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveSlot2Button.shape.setPosition(saveSlot2Button.getInitialPosition());
	}

	if (saveSlot3Button.shape.getGlobalBounds().contains(mouseCoords)) {
		saveSlot3Button.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveSlot3Button.shape.setPosition({ saveSlot3Button.getInitialPosition().x,  saveSlot3Button.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				if (!isEmptySaveSlot3) {
					// load from file to game
					loadGameFromFile(saveFileName3);
					return;
				}
				else {
					shouldDrawEmptySaveSlot3 = true;
					slotEmptyText.setPosition({ saveSlot3Button.getInitialPosition().x + saveSlot3Button.shape.getSize().x - 20, saveSlot3Button.getInitialPosition().y });
				}
			}
		}
	}
	else {
		saveSlot3Button.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveSlot3Button.shape.setPosition(saveSlot3Button.getInitialPosition());
	}

	if (saveSlot4Button.shape.getGlobalBounds().contains(mouseCoords)) {
		saveSlot4Button.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveSlot4Button.shape.setPosition({ saveSlot4Button.getInitialPosition().x,  saveSlot4Button.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				if (!isEmptySaveSlot4) {
					// load from file to game
					loadGameFromFile(saveFileName4);
					return;
				}
				else {
					shouldDrawEmptySaveSlot4 = true;
					slotEmptyText.setPosition({ saveSlot4Button.getInitialPosition().x + saveSlot4Button.shape.getSize().x - 20, saveSlot4Button.getInitialPosition().y });
				}
			}
		}
	}
	else {
		saveSlot4Button.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveSlot4Button.shape.setPosition(saveSlot4Button.getInitialPosition());
	}
}

void LoadGameState::update(float dt) {}

void LoadGameState::render() {
	window->draw(loadGameBackgroundSprite);
	window->draw(loadGameText);
	window->draw(goBackArrowSprite); if (shouldDrawEmptySaveSlot1 || shouldDrawEmptySaveSlot2 || shouldDrawEmptySaveSlot3 || shouldDrawEmptySaveSlot4)
	window->draw(slotEmptyText);
	window->draw(saveSlot1Button);
	window->draw(saveSlot2Button);
	window->draw(saveSlot3Button);
	window->draw(saveSlot4Button);
}

void LoadGameState::loadGameFromFile(const string& saveFileName) {
	std::ifstream fin(saveFileName);
	if (fin.fail()) {
		throw std::runtime_error("Cannot open Save File");
	}

	MapID currentMap;
	std::string tmpMapId;
	fin >> tmpMapId;

	if (tmpMapId == "Map1") {
		currentMap = MapID::Map1;
	}
	else if (tmpMapId == "Map2") {
		currentMap = MapID::Map2;
	}
	else if (tmpMapId == "Map3") {
		currentMap = MapID::Map3;
	}
	else if (tmpMapId == "Map4") {
		currentMap = MapID::Map4;
	}

	auto playState = std::make_unique<PlayState>(window, states, currentMap);
	playState->load(fin);
	states->push(std::move(playState));
}

bool LoadGameState::fileExist(const std::string& filePath) {
	std::ifstream file(filePath);
	return !file.good();//Return true if empty slot Save
}

void LoadGameState::checkSaveSlots() {//Check see if file save already exist
	isEmptySaveSlot1 = fileExist(saveFileName1);
	isEmptySaveSlot2 = fileExist(saveFileName2);
	isEmptySaveSlot3 = fileExist(saveFileName3);
	isEmptySaveSlot4 = fileExist(saveFileName4);
}