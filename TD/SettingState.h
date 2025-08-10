#pragma once

#include "Resource_Management.h"
#include "SoundManager.h"
#include "State.h"
#include "Sprite.h"
#include "Button.h"
#include "MusicSlider.h"
#include "SoundSlider.h"

class SettingState : public State {

public:
	SettingState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::Text settingText = sf::Text(Resource_Management::font, "SETTINGS");
	sf::Text musicVolumeText = sf::Text(Resource_Management::font, "Music Volume");
	sf::Text soundVolumeText = sf::Text(Resource_Management::font, "Sound Volume");
	Sprite settingBackgroundSprite = Sprite(Resource_Management::loadGameBackgroundTexture);
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	Sprite goBackArrowSprite = Sprite(Resource_Management::leftArrowTexture, { 36, 36 });
	MusicSlider musicSlider = MusicSlider({ Resource_Management::WINDOW_WIDTH / 2.f, Resource_Management::WINDOW_HEIGHT / 2.f - 20 });
	SoundSlider soundSlider = SoundSlider({ Resource_Management::WINDOW_WIDTH / 2.f, Resource_Management::WINDOW_HEIGHT / 2.f + 100 });
};