#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SFML\Graphics.hpp"
#include <vector>
#include "tool.h"
#include "enemy.h"
#include "tower.h"

class mapTowerDefense_Game {

private:

	//Matrix mapTowerDefense_Game
	std::vector<std::vector<point>> _m;

	//////////////////Texture///////////////////////////////////
	int totalFrame = 0;
	float frameTime = 0.3F; // 1frame/2 second
	float timeSinceLastFrame = 0.0F;
	int currentFrame = 0;

	std::vector<sf::Texture> Map_GameTexture;
	sf::Sprite Map_GameSprite;
	void animate(float);
	///////////////////////////////////////////////////////////

public:
	mapTowerDefense_Game(const std::vector<sf::Texture>& rMap_GameTexture);
	// -1 là tường, 0 là trống, 1 là tower
	//void resetMap_GameData();
	void makeMap_GameData();
	bool ReadFile(std::string fileName);

	void Update(float);
	void draw(sf::RenderWindow& window);

	void setTotalFrame(int rFrameNum) { totalFrame = rFrameNum; }
	vector<vector<point>> getMap_Game(){
		return _m;
	}
};

