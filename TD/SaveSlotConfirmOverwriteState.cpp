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
	confirmText.setCharacterSize(24);
	confirmText.setOrigin({ confirmText.getLocalBounds().position + confirmText.getLocalBounds().size / 2.0f });
	confirmText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40 });
}

void SaveSlotConfirmOverwriteState::handleInput(const std::optional<sf::Event>& event) {

	if (!event.has_value()) return;

	sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (yesButton.shape.getGlobalBounds().contains(mouseCoords)) {
		yesButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		yesButton.shape.setPosition({ yesButton.getInitialPosition().x,  yesButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				std::ofstream fileOut(fileName);
				if (fileOut.fail()) {
					throw std::runtime_error("Cannot Save File write File");
				}
				GameSaver::saveGame(fileOut);
				quit = true;
				numPop = 1;
				return;
			}
		}
	}
	else {
		yesButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		yesButton.shape.setPosition(yesButton.getInitialPosition());
	}

	if (noButton.shape.getGlobalBounds().contains(mouseCoords)) {
		noButton.shape.setFillColor(Resource_Management::colorWhenClickOnButton);
		noButton.shape.setPosition({ noButton.getInitialPosition().x,  noButton.getInitialPosition().y - 2.0f });
		if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (keyPressed->button == sf::Mouse::Button::Left) {
				quit = true;
				numPop = 1;
				return;
			}
		}
	}
	else {
		noButton.shape.setFillColor(Resource_Management::buttonShapeFillColor);
		noButton.shape.setPosition(noButton.getInitialPosition());
	}
}

void SaveSlotConfirmOverwriteState::update(float dt) {}

void SaveSlotConfirmOverwriteState::render() {
	window->draw(popUpShape);
	window->draw(confirmText);
	window->draw(yesButton);
	window->draw(noButton);
}