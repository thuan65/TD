#include "LoadingBeforePlayState.h"

LoadingBeforePlayState::LoadingBeforePlayState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));
}

void LoadingBeforePlayState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {
	if (!event.has_value()) return;
}

void LoadingBeforePlayState::update(float dt, sf::Vector2f mouseCoords) {
	timeAccumulator += dt;

	if (timeAccumulator >= frameSwitchTime / 4.f) {
		timeAccumulator = 0;
		++currentFrame;
		if (currentFrame == 5) {
			quit = true;
			numPop = 1;
			SoundManager::stopMusic();
			return;
		}
		loadingFrame.setTexture(Resource_Management::loadingFrameTexture[currentFrame]);
	}
}

void LoadingBeforePlayState::render() {
	window->draw(backgroundSprite);
	window->draw(dimOverlay);
	window->draw(loadingFrame);
}