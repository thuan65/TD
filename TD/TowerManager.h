#pragma once
#include "tower.h"
#include "enemy.h"
#include "BulletManager.h"
#include "Resource_Management.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

class TowerManager{

private: 

	struct buildZone {
		sf::FloatRect bounds;
		bool TowerExist = false;
	};
	
	BulletManager* bulletManager;
	std::vector<tower*> towers;
	std::vector<buildZone> buildZones;

public:

	TowerManager(BulletManager* rbulletManager = nullptr);
	~TowerManager();

	void update(float deltaTime, std::vector<enemy*>& enemies);//Kiem soat viec dan ban
	bool towerTowerExisted(sf::Vector2f worldPos);
	void ReadFile(const std::string& filePath);
	bool clickCheck(sf::Vector2f);
	void buildTower(sf::Vector2f worldPos, const std::string& towerType);
	void sellTower();
	void upgrateTower();

	void draw(sf::RenderWindow& window);
};

