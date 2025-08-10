#pragma once

#include "State.h"
#include "Resource_Management.h"

class SaveSlotSuccessfulState : public State {

public:
	SaveSlotSuccessfulState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void  handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::RectangleShape popUpShape = sf::RectangleShape({ 250, 120 });
	sf::Text text = sf::Text(Resource_Management::font, "Save Successful!", 20);

	float timeAccumulator = 0.0f;
};

