#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "Button.h"
#include "GameSaver.h"
#include <string>
#include <fstream>

class SaveSlotConfirmOverwriteState : public State {

public:
	SaveSlotConfirmOverwriteState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, const std::string& fileName);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;

private:
	sf::RectangleShape popUpShape = sf::RectangleShape({250, 120});
	sf::Text confirmText = sf::Text(Resource_Management::arialFont, "Overwrite Save File?");
	Button yesButton = Button({ 50, 50 }, { Resource_Management::WINDOW_WIDTH / 2.0f - 50, Resource_Management::WINDOW_HEIGHT / 2.0f + 20 }, "Yes");
	Button noButton = Button({ 50, 50 }, { Resource_Management::WINDOW_WIDTH / 2.0f + 50, Resource_Management::WINDOW_HEIGHT / 2.0f + 20 }, "No");
	std::string fileName;
};

