#include "Sprite.h"
#include "SoundSlider.h"

Sprite::Sprite(const sf::Texture& texture, sf::Vector2f initialPosition) :
	sf::Sprite(texture),
	initialPosition(initialPosition) {
	this->setOrigin({ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });
	this->setPosition(initialPosition);
}

bool Sprite::isClicked(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {
	if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (keyPressed->button == sf::Mouse::Button::Left) {
			if (this->getGlobalBounds().contains(mouseCoords)) {
				return true;
			}
		}
	}
	return false;
}

void Sprite::update(sf::Vector2f mouseCoords) {
	if (this->getGlobalBounds().contains(mouseCoords))
		this->setPosition(this->initialPosition + sf::Vector2f(0.0f, -2.0f));
	else this->setPosition(this->initialPosition);
}