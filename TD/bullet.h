#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class enemy;
class tower;

class bullet {

public:
	bullet(const std::vector<sf::Texture>& bulletTexure, int _speed = 500, int rdamage = 100);
	void Initialize(tower* theTower, enemy* theTarget);//Use for calc the vi tri can toi
	void Update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return bulletSprite.getPosition(); }
	float getTimeBeforeCollide() { return timeBeforeCollide; }
	enemy* getTarget() { return target; }
	int getDamage() { return damage; }

private:
	sf::Sprite bulletSprite;
	sf::Vector2f bulletDirection; // Huong di cua bullet trong tung frame
	float timeBeforeCollide = 0.0f;

	enemy* target;
	int _speed;
	int damage;

};
