#include "SaveGameState.h"

SaveGameState::SaveGameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));

	saveGameText.setFillColor(sf::Color::White);
	saveGameText.setOutlineColor(sf::Color::Black);
	saveGameText.setOutlineThickness(5.0f);
	saveGameText.setCharacterSize(32);
	saveGameText.setOrigin({ saveGameText.getLocalBounds().position + saveGameText.getLocalBounds().size / 2.0f });
	saveGameText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 30 });
	goBackArrowSprite.setScale({ 0.4f, 0.4f });
	checkSaveSlots();
}

void SaveGameState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (goBackArrowSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (saveSlot1Button.shape.getGlobalBounds().contains(mouseCoords)) {
		saveSlot1Button.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveSlot1Button.shape.setPosition({ saveSlot1Button.getInitialPosition().x,  saveSlot1Button.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				if (!isFullSaveSlot1) {
					// save file
					states->push(std::make_unique<SaveSlotSuccessfulState>(window, states));
					isFullSaveSlot1 = true;
					saveGame(saveFileName1);
					quit = true;
					numPop = 1;
					return;
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName1));
				}
				SoundManager::playSound(Resource_Management::buttonClickSound);
				return;
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
				if (!isFullSaveSlot2) {
					// save file
					states->push(std::make_unique<SaveSlotSuccessfulState>(window, states));
					isFullSaveSlot2 = true;
					saveGame(saveFileName2);
					quit = true;
					numPop = 1;
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName2));
				}
				SoundManager::playSound(Resource_Management::buttonClickSound);
				return;
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
				if (!isFullSaveSlot3) {
					// save file
					states->push(std::make_unique<SaveSlotSuccessfulState>(window, states));
					isFullSaveSlot3 = true;
					saveGame(saveFileName3);
					quit = true;
					numPop = 1;
					
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName3));
				}
				SoundManager::playSound(Resource_Management::buttonClickSound);
				return;
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
				if (!isFullSaveSlot4) {
					// save file
					states->push(std::make_unique<SaveSlotSuccessfulState>(window, states));
					isFullSaveSlot4 = true;
					saveGame(saveFileName4);
					quit = true;
					numPop = 1;
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName4));
				}
				SoundManager::playSound(Resource_Management::buttonClickSound);
				return;
			}
		}
	}
	else {
		saveSlot4Button.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveSlot4Button.shape.setPosition(saveSlot4Button.getInitialPosition());
	}
}

void SaveGameState::update(float dt, sf::Vector2f mouseCoords) {
	goBackArrowSprite.update(mouseCoords);
}

void SaveGameState::render() {
	window->draw(loadGameBackgroundSprite);
	window->draw(dimOverlay);
	window->draw(saveGameText);
	window->draw(goBackArrowSprite);
	window->draw(saveSlot1Button);
	window->draw(saveSlot2Button);
	window->draw(saveSlot3Button);
	window->draw(saveSlot4Button);
}

bool SaveGameState::fileExist(const std::string& filePath) {
	std::ifstream file(filePath);
	return file.good();
}

void SaveGameState::checkSaveSlots() {//Check see if file save already exist
	isFullSaveSlot1 = fileExist(saveFileName1);
	isFullSaveSlot2 = fileExist(saveFileName2);
	isFullSaveSlot3 = fileExist(saveFileName3);
	isFullSaveSlot4 = fileExist(saveFileName4);
}

void SaveGameState::saveGame(const std::string& fileName) {
	std::ofstream fout(fileName);
	if (fout.fail()) {
		throw std::runtime_error("Cannot Save File write File");
	}
	GameSaver::saveGame(fout);
	fout.close();
}
