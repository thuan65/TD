#pragma once
#include "point.h"
#include "enemy.h"
#include "MathHelpers.h"
#include "SFML/Graphics.hpp"
#include <vector>

class BulletManager;

class tower {
	std::vector<sf::Texture> towerTexture;
	sf::Sprite towerSprite;

	float range;
	float FireRate;
	float towerReloading = 0.0f;
	int row, col;

	//point _location; //This is location of the tower
	//bullet _b;//Cái viên đạn mà tháp bắn ra

public:
	tower(const std::vector<sf::Texture>& rtowerTexture, int row = 0, int col = 0, float rRange = 150.0f, float rFireRate = 2); //Change the range setting later
	enemy* findTheNearestEnemyInRange(std::vector<enemy*>& enemies);


	void update(const float& deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager);
	void draw(sf::RenderWindow& window);

	void setPosition(const point &_rlocation) {
		towerSprite.setPosition(sf::Vector2f(_rlocation.getX() * point::TileSize, _rlocation.getY() * point::TileSize));
	}
	sf::Vector2f getPosition() {
		return towerSprite.getPosition();
	}
	int getRow() { return row; }
	int getCol() { return col; }

	//void setMap_GameForBullet(point[][point::Map_Game_SIZE]);
	//void calcPathBullet() {
	//	_b.calcPathBullet(_location);
	//}

	//bullet& getBullet() { return _b; }
};

