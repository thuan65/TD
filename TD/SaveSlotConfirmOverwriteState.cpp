#include "SaveSlotConfirmOverwriteState.h"

SaveSlotConfirmOverwriteState::SaveSlotConfirmOverwriteState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, const std::string& fileName) :
	State(window, states),
	fileName(fileName)
{
	allowRenderBelow = true;

	popUpShape.setOrigin(popUpShape.getGeometricCenter());
	popUpShape.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f });
	popUpShape.setFillColor(sf::Color::White);
	popUpShape.setOutlineColor(sf::Color::Black);
	popUpShape.setOutlineThickness(5.0f);

	confirmText.setFillColor(sf::Color::White);
	confirmText.setOutlineColor(sf::Color::Black);
	confirmText.setOutlineThickness(5.0f);
	confirmText.setOrigin({ confirmText.getLocalBounds().position + confirmText.getLocalBounds().size / 2.0f });
	confirmText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40 });

	yesIconSprite.setScale({ 0.6f, 0.6f });
	noIconSprite.setScale({ 0.6f, 0.6f });
}

void SaveSlotConfirmOverwriteState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (yesIconSprite.isClicked(event, mouseCoords)) {
		//Save Game
		std::ofstream fileOut(fileName);
		if (fileOut.fail()) {
			throw std::runtime_error("Cannot Save File write File");
		}
		GameSaver::saveGame(fileOut);
		states->push(std::make_unique<SaveSlotSuccessfulState>(window, states));
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	if (noIconSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}
}

void SaveSlotConfirmOverwriteState::update(float dt, sf::Vector2f mouseCoords) {
	yesIconSprite.update(mouseCoords);
	noIconSprite.update(mouseCoords);
}

void SaveSlotConfirmOverwriteState::render() {
	window->draw(popUpShape);
	window->draw(confirmText);
	window->draw(yesIconSprite);
	window->draw(noIconSprite);
}