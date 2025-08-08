#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f initialPosition, const std::string& textString, sf::Color shapeFillColor, sf::Color textFillColor, sf::Color shapeOutlineColor, float shapeOutlineThickness, sf::Color textOutlineColor, float textOutlineThickness) :
	shape(size),
	text(Resource_Management::arialFont, textString),
	initialPosition(initialPosition) {
	shape.setOrigin(size / 2.0f);
	shape.setPosition(initialPosition);
	shape.setFillColor(shapeFillColor);
	shape.setOutlineColor(shapeOutlineColor);
	shape.setOutlineThickness(shapeOutlineThickness);
	text.setOrigin({ text.getLocalBounds().position + text.getLocalBounds().size / 2.0f });
	text.setPosition(initialPosition);
	text.setFillColor(textFillColor);
	text.setOutlineColor(textOutlineColor);
	text.setOutlineThickness(textOutlineThickness);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
	target.draw(text, states);
}
