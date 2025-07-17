#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H

#include "SFML/Graphics.hpp"

namespace MathHelpers {
	float static Distance(const sf::Vector2f pos, const sf::Vector2f des) {
		sf::Vector2f delta = des - pos;
		return sqrt(delta.x * delta.x + delta.y * delta.y);
	}
}



#endif // !MATH_HELPERS_H
