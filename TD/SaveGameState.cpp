#include "SaveGameState.h"

SaveGameState::SaveGameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	saveGameText.setFillColor(sf::Color::White);
	saveGameText.setOutlineColor(sf::Color::Black);
	saveGameText.setOutlineThickness(5.0f);
	saveGameText.setCharacterSize(32);
	saveGameText.setOrigin({ saveGameText.getLocalBounds().position + saveGameText.getLocalBounds().size / 2.0f });
	saveGameText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 30 });
	goBackArrowSprite.setScale({ 0.2f, 0.2f });
	goBackArrowSprite.rotate(sf::degrees(180));
	checkSaveSlots();
}

void SaveGameState::handleInput(const std::optional<sf::Event>& event) {

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

	if (saveSlot1Button.shape.getGlobalBounds().contains(mouseCoords)) {
		saveSlot1Button.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		saveSlot1Button.shape.setPosition({ saveSlot1Button.getInitialPosition().x,  saveSlot1Button.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
			
				if (!isFullSaveSlot1) {
					// save file
					std::ofstream fout(saveFileName1);
					if (fout.fail()) {
						throw std::runtime_error("Cannot Save File write File");
					}
					GameSaver::saveGame(fout);
					quit = true;
					numPop = 1;
					fout.close();
					return;
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName1));
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
				if (!isFullSaveSlot2) {
					// save file
					std::ofstream fout(saveFileName2);
					if (fout.fail()) {
						throw std::runtime_error("Cannot Save File write File");
					}
					GameSaver::saveGame(fout);
					quit = true;
					numPop = 1;
					fout.close();
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName2));
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
				if (!isFullSaveSlot3) {
					// save file
					std::ofstream fout(saveFileName3);
					if (fout.fail()) {
						throw std::runtime_error("Cannot Save File write File");
					}
					GameSaver::saveGame(fout);
					quit = true;
					numPop = 1;
					fout.close();
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName3));
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
				if (!isFullSaveSlot4) {
					// save file
					std::ofstream fout(saveFileName4);
					if (fout.fail()) {
						throw std::runtime_error("Cannot Save File write File");
					}
					GameSaver::saveGame(fout);
					quit = true;
					numPop = 1;
					fout.close();
				}
				else {
					states->push(std::make_unique<SaveSlotConfirmOverwriteState>(window, states, saveFileName4));
				}
			}
		}
	}
	else {
		saveSlot4Button.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		saveSlot4Button.shape.setPosition(saveSlot4Button.getInitialPosition());
	}
}

void SaveGameState::update(float dt) {}

void SaveGameState::render() {
	window->draw(loadGameBackgroundSprite);
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
