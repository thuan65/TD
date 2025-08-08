//

#pragma once
#include "point.h"
#include "MathHelpers.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>


class enemy;
class BulletManager;

class tower {
private:
	std::vector<sf::Texture> towerTexture;
	sf::Sprite towerSprite;

	float range, FireRate;
	int damage;
	float towerReloading;
	int row, col;

	int level, upgradeCost, sellValue;
	std::string towerType;

	int currentFrame;
	float frameTime, timeSinceLastFrame;
	int totalFrame;

	enemy* findTheNearestEnemyInRange(std::vector<enemy*>& enemies);
	void animate(float deltaTime);

public:
	// CONSTRUCTOR ĐÚNG
	tower(const std::string& type, const std::vector<sf::Texture>& rtowerTexture, int row, int col);

	void update(float deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager);
	void draw(sf::RenderWindow& window);
	void upgrade();

	void setPosition(sf::Vector2f position); // Chỉ khai báo
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	int getRow() const { return row; }
	int getCol() const { return col; }
	int getUpgradeCost() const { return upgradeCost; }
	int getSellValue() const { return sellValue; }
};