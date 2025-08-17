#pragma once
#include "point.h"
#include "MathHelpers.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>


class enemy;
class BulletManager;

class tower {
protected:
	const std::vector<sf::Texture>* towerTexture;
	std::string towerType;
	sf::Sprite towerSprite;

	float range, fireRate;
	int damage;
	float reloadTime;

	int level, upgradeCost, sellValue;


	int currentFrame;
	float frameTime, timeSinceLastFrame;
	int totalFrame;

	enemy* findTheNearestEnemyInRange(std::vector<enemy*>& enemies);
	void animate(float deltaTime);

public:
	// CONSTRUCTOR
	tower(const std::string& type);
	virtual ~tower() {}

	virtual void update(float deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager);
	virtual void upgrade();

	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f position); // Chỉ khai báo
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	int getUpgradeCost() const { return upgradeCost; }
	int getSellValue() const { return sellValue; }
	int getTowerLevel() { return level; }
	std::string getTowerType() { return towerType; }


	virtual void updadeToLevel(int level);
};