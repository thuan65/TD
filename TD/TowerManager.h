#pragma once
#include "tower.h"
#include "enemy.h"
#include "BulletManager.h"
#include "Resource_Management.h"
#include <vector>

class TowerManager{

private: 
	
	BulletManager* bulletManager;
	std::vector<tower*> towers;

public:

	TowerManager(BulletManager* rbulletManager = nullptr);
	~TowerManager();

	void update(float deltaTime, std::vector<enemy*>& enemies);//Kiem soat viec dan ban
	bool towerTowerExisted(int row, int col);
	void buildTower(int row, int col, const std::string& towerType);
	void sellTower();
	void upgrateTower();

	void draw(sf::RenderWindow& window);
};

