#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "SoundManager.h"
#include "Button.h"
#include "GameSaver.h"
#include "SaveSlotSuccessfulState.h"
#include <string>
#include <fstream>

class SaveSlotConfirmOverwriteState : public State {

public:
	SaveSlotConfirmOverwriteState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, const std::string& fileName);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::RectangleShape popUpShape = sf::RectangleShape({ 300, 120 });
	sf::Text confirmText = sf::Text(Resource_Management::font, "Overwrite Save File?", 20);
	Sprite yesIconSprite = Sprite(Resource_Management::yesIconTexture, { Resource_Management::WINDOW_WIDTH / 2.0f - 50, Resource_Management::WINDOW_HEIGHT / 2.0f + 20 });
	Sprite noIconSprite = Sprite(Resource_Management::noIconTexture, { Resource_Management::WINDOW_WIDTH / 2.0f + 50, Resource_Management::WINDOW_HEIGHT / 2.0f + 20 });
	std::string fileName;//The Name of the file Save
};