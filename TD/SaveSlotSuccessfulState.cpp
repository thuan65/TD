#include "SaveSlotSuccessfulState.h"

SaveSlotSuccessfulState::SaveSlotSuccessfulState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	allowRenderBelow = true;

	popUpShape.setOrigin(popUpShape.getGeometricCenter());
	popUpShape.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f });
	popUpShape.setFillColor(sf::Color::White);
	popUpShape.setOutlineColor(sf::Color::Black);
	popUpShape.setOutlineThickness(5.0f);

	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5.0f);
	text.setOrigin({ text.getLocalBounds().position + text.getLocalBounds().size / 2.0f });
	text.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f });
}

void SaveSlotSuccessfulState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {}

void SaveSlotSuccessfulState::update(float dt, sf::Vector2f mouseCoords) {
	timeAccumulator += dt;
	if (timeAccumulator >= frameSwitchTime / 2) {
		std::vector<State*> toGoBack;

		// Traverse stack from top to bottom and gather states to go back
		for (auto it = states->_Get_container().rbegin(); it != states->_Get_container().rend(); ++it) {
			if (!(*it)->shouldAllowRenderBelow()) break;
			toGoBack.push_back(it->get());
		}
		if (toGoBack.size() == 1) numPop = 1;
		else if (toGoBack.size() == 2) numPop = 2;
		else throw "wrong logic in SaveSlotSuccessfulState::update";
		quit = true;
	}
}

void SaveSlotSuccessfulState::render() {
	window->draw(popUpShape);
	window->draw(text);
}