#pragma once
#include "tower.h"
#include "enemy.h"
#include "BulletManager.h"
#include "Resource_Management.h"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <vector>

class TowerManager{

private: 
	
	BulletManager* bulletManager;
	std::vector<tower*> towers;
	std::vector<sf::FloatRect> buildZone;

public:

	TowerManager(BulletManager* rbulletManager = nullptr);
	~TowerManager();

	void update(float deltaTime, std::vector<enemy*>& enemies);//Kiem soat viec dan ban
	bool towerTowerExisted(int row, int col);
	void ReadFile(const std::string& filePath);
	bool clickCheck(sf::Vector2f);
	void buildTower(int row, int col, const std::string& towerType);
	void sellTower();
	void upgrateTower();

	void draw(sf::RenderWindow& window);
};

