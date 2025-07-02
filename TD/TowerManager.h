#pragma once
#include "tower.h"
#include "Resource_Management.h"

class TowerManager{

private: 
	
	std::vector<tower*> towers;

public:

	TowerManager() {};
	~TowerManager();

	void buildTower(int row, int col);//Sau này tham số sẽ là id (loại tháp) của tháp muốn build
	void sellTower();
	void upgrateTower();

	void draw(sf::RenderWindow& window);
};

