#include "Slider.h"

Slider::Slider(sf::Vector2f position, float initialValue) :
	//size(size),
	position(position),
	value(std::clamp(initialValue, 0.f, 100.f)) {

	barSprite.setOrigin(barSprite.getGlobalBounds().size / 2.0f);
	barSprite.setPosition(position);

	knobSprite.setOrigin(knobSprite.getGlobalBounds().size / 2.0f);
	setKnobPosition(value);

	//bar.setSize(size);
	//bar.setOrigin(bar.getGeometricCenter());
	//bar.setPosition(position);
	//bar.setFillColor(sf::Color::Blue);

	//knob.setRadius(size.y / 2.f);
	//knob.setOrigin(knob.getGeometricCenter());
	//knob.setFillColor(sf::Color::White);
	//setKnobPosition(value);
}

void Slider::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {
	if (!event.has_value()) return;

	//float leftX = position.x - (size.x / 2.f) + knob.getRadius();
	//float rightX = position.x + (size.x / 2.f) - knob.getRadius();
	float leftX = position.x - (barSprite.getGlobalBounds().size.x / 2.f) + (knobSprite.getGlobalBounds().size.x / 2.f);
	float rightX = position.x + (barSprite.getGlobalBounds().size.x / 2.f) - (knobSprite.getGlobalBounds().size.x / 2.f);

	if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePressed->button == sf::Mouse::Button::Left && barSprite.getGlobalBounds().contains(mouseCoords)) {
			dragging = true;
		}
	}

	if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
		if (mouseReleased->button == sf::Mouse::Button::Left) {
			dragging = false;
		}
	}
}

void Slider::setValue(float v) {
	value = std::clamp(v, 0.f, 100.f);
	setKnobPosition(value);
}

float Slider::getValue() const {
	return value;
}

void Slider::setKnobPosition(float v) {
	/*float leftX = position.x - (size.x / 2.f) + knob.getRadius();
	float rightX = position.x + (size.x / 2.f) - knob.getRadius();
	float knobX = leftX + (value / 100.f) * (rightX - leftX);
	knob.setPosition({ knobX, position.y });*/

	float leftX = position.x - (barSprite.getGlobalBounds().size.x / 2.f) + (knobSprite.getGlobalBounds().size.x / 2.f);
	float rightX = position.x + (barSprite.getGlobalBounds().size.x / 2.f) - (knobSprite.getGlobalBounds().size.x / 2.f);
	float knobX = leftX + (value / 100.f) * (rightX - leftX);
	knobSprite.setPosition({ knobX, position.y });
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const {
	target.draw(barSprite, renderStates);
	target.draw(knobSprite, renderStates);
}
