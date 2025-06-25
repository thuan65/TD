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

class map {

private:

	//Matrix map
	std::vector<std::vector<point>> _m;


	//////////////////Texture///////////////////////////////////
	int totalFrame = 0;
	float frameTime = 0.3F; // 1frame/2 second
	float timeSinceLastFrame = 0.0F;
	int currentFrame = 0;

	std::vector<sf::Texture> mapTexture;
	std::vector<sf::Sprite> mapSprite;

	void LoadTexture();
	void animate(float);
	///////////////////////////////////////////////////////////

public:
	map();
	// -1 là tường, 0 là trống, 1 là tower
	//void resetMapData();
	void makeMapData();
	bool ReadFile(std::string fileName);

	void Update(float);
	void drawMap(sf::RenderWindow& window);

	void setTotalFrame(int rFrameNum) { totalFrame = rFrameNum; }
	vector<vector<point>> getMap(){
		return _m;
	}



};

