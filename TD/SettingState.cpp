#include "SettingState.h"

SettingState::SettingState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states) :
	State(window, states) {
	dimOverlay.setFillColor(sf::Color(0, 0, 0, 128));

	settingText.setFillColor(sf::Color::White);
	settingText.setOutlineColor(sf::Color::Black);
	settingText.setOutlineThickness(5.0f);
	settingText.setCharacterSize(32);
	settingText.setOrigin({ settingText.getLocalBounds().position + settingText.getLocalBounds().size / 2.0f });
	settingText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.0f, 30 });

	musicVolumeText.setFillColor(sf::Color::White);
	musicVolumeText.setOutlineColor(sf::Color::Black);
	musicVolumeText.setOutlineThickness(2.0f);
	musicVolumeText.setCharacterSize(24);
	musicVolumeText.setOrigin({ musicVolumeText.getLocalBounds().position + musicVolumeText.getLocalBounds().size / 2.0f });
	musicVolumeText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.f, Resource_Management::WINDOW_HEIGHT / 2.f - 60 });

	soundVolumeText.setFillColor(sf::Color::White);
	soundVolumeText.setOutlineColor(sf::Color::Black);
	soundVolumeText.setOutlineThickness(2.0f);
	soundVolumeText.setCharacterSize(24);
	soundVolumeText.setOrigin({ soundVolumeText.getLocalBounds().position + soundVolumeText.getLocalBounds().size / 2.0f });
	soundVolumeText.setPosition({ Resource_Management::WINDOW_WIDTH / 2.f, Resource_Management::WINDOW_HEIGHT / 2.f + 60 });

	goBackArrowSprite.setScale({ 0.4f, 0.4f });
}

void SettingState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

	if (!event.has_value()) return;

	if (goBackArrowSprite.isClicked(event, mouseCoords)) {
		quit = true;
		numPop = 1;
		SoundManager::playSound(Resource_Management::buttonClickSound);
		return;
	}

	musicSlider.handleInput(event, mouseCoords);
	soundSlider.handleInput(event, mouseCoords);
}

void SettingState::update(float dt, sf::Vector2f mouseCoords) {
	goBackArrowSprite.update(mouseCoords);
	musicSlider.update(mouseCoords);
	soundSlider.update(mouseCoords);
}

void SettingState::render() {
	window->draw(settingBackgroundSprite);
	window->draw(dimOverlay);
	window->draw(settingText);
	window->draw(musicVolumeText);
	window->draw(soundVolumeText);
	window->draw(goBackArrowSprite);
	window->draw(musicSlider);
	window->draw(soundSlider);
}