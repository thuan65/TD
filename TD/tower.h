#pragma once
#include "point.h"
#include "enemy.h"
#include "MathHelpers.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class BulletManager;

class tower {
private:
	std::vector<sf::Texture> towerTexture;
	sf::Sprite towerSprite;

	float range;//Phạm vi bắn
	float FireRate;//Tốc độ bắn
	int damage;
	float towerReloading = 0.0f;//Thời gian hồi tới lượt bắn kế
	int row, col;

	int level;
	int upgradeCost;
	int sellValue;
	std::string towerType;

	

	////////////Animation_helper//////////
	int currentFrame = 0;
	float frameTime = 0.5F;
	float timeSinceLastFrame = 0.0F;
	int totalFrame;

	//point _location; //This is location of the tower
	//bullet _b;//Cái viên đạn mà tháp bắn ra

public:
	//tower(const std::vector<sf::Texture>& rtowerTexture, int row = 0, int col = 0, float rRange = 150.0f, float rFireRate = 2); //Change the range setting later
	tower(const std::string& type, const std::vector<sf::Texture>& rtowerTexture);
	/*enemy* findTheNearestEnemyInRange(std::vector<enemy*>& enemies);*/ // Thành private 

	/*void animate(float deltaTime);*/ // private
	void update(const float& deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager);
	void draw(sf::RenderWindow& window);

	// Hàm nâng cấp 
	void upgrade();

	// Các hàm getter

	sf::FloatRect getGlobalBounds() const;
	int getRow() const { return row; }
	int getCol() const { return col; }
	int getUpgradeCost() const { return upgradeCost; }
	int getSellValue() const { return sellValue; }
	int getLevel() const { return level; }
	std::string getType() const { return towerType; }

	void setPosition(sf::Vector2f _rlocation) {
		towerSprite.setPosition(_rlocation);
	}
	sf::Vector2f getPosition() const {
		return towerSprite.getPosition();
	}
	//int getRow() { return row; }
	//int getCol() { return col; }

	//void setMap_GameForBullet(point[][point::Map_Game_SIZE]);
	//void calcPathBullet() {
	//	_b.calcPathBullet(_location);
	//}

	//bullet& getBullet() { return _b; }

private:
	enemy* findTheNearestEnemyInRange(std::vector<enemy*>& enemies);
	void animate(float deltaTime);
};

