#pragma once
//Done
#include "SFML/Graphics.hpp"
#include "Resource_Management.h"
#include <string>

class MainMenuState;
class PauseState;
class VictoryState;
class LoseState;

class Button : public sf::Drawable {
public:
	sf::RectangleShape shape;

private:
	sf::Text text;
	sf::Vector2f initialPosition;

public:
	Button(sf::Vector2f size, sf::Vector2f initialPosition, const std::string& textString = "button", sf::Color shapeFillColor = sf::Color(111, 111, 111), sf::Color textFillColor = sf::Color(226, 226, 226), sf::Color shapeOutlineColor = sf::Color::Black, float shapeOutlineThickness = 2.0f, sf::Color textOutlineColor = sf::Color::White, float textOutlineThickness = 0.0f);

	sf::Vector2f getInitialPosition() const { return initialPosition; }

	/*sf::RectangleShape getShape() const { return shape; }
	sf::Text getText() const { return text; }
	void setShape(sf::RectangleShape shape) { this->shape = shape; }
	void setText(sf::Text text) { this->text = text; }*/

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	friend class MainMenuState;
	friend class PauseState;
	friend class VictoryState;
	friend class LoseState;
};

