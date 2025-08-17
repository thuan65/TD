#include "CountdownState.h"

CountdownState::CountdownState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	allowRenderBelow = true;
	allowUpdateBelow = false;

	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));

	countdownText.setFillColor(sf::Color::White);
	countdownText.setOutlineColor(sf::Color::Black);
	countdownText.setOutlineThickness(10.0f);
	countdownText.setOrigin({ countdownText.getLocalBounds().position + countdownText.getLocalBounds().size / 2.0f });
	countdownText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.f, Resource_Management::WINDOW_HEIGHT / 2.f });

	SoundManager::playSound(Resource_Management::boomSound);
}

void CountdownState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {
	if (!event.has_value()) return;
}

void CountdownState::update(float dt, sf::Vector2f mouseCoords) {
	timeAccumulator += dt;

	if (timeAccumulator >= frameSwitchTime / 2.f) {
		timeAccumulator = 0;
		if (count == 0) {
			quit = true;
			numPop = 1;
			SoundManager::playPlayMusic();
			return;
		}
		--count;
		if (count == 2) countdownText.setString("2");
		else if (count == 1) countdownText.setString("1");
		else countdownText.setString("GO");
		countdownText.setOrigin({ countdownText.getLocalBounds().position + countdownText.getLocalBounds().size / 2.0f });
		countdownText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.f, Resource_Management::WINDOW_HEIGHT / 2.f });

		SoundManager::playSound(Resource_Management::boomSound);
	}
}

void CountdownState::render() {
	window->draw(dimOverlay);
	window->draw(countdownText);
}
