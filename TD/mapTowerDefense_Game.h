#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SFML\Graphics.hpp"
#include "enemy.h"
#include "tower.h"
#include "PathFinder.h"
#include "gameSate.h"

class mapTowerDefense_Game {

private:

	std::string filePathForMatrixLogic;
	std::string filePathForStartEndPosition;

	/////////////////Map Logic////////////////////////////////
	//Matrix mapTowerDefense_Game
	std::vector<std::vector<point>> _Map_Game_Logic;
	point startPos, endDes;//Starting Point and destination point of the path

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
	void findSecondPath();
	bool ReadFile(std::string fileName);
	void setFilePath(const::string& filePath);//The file path to the map logic matrix
	void setFilePathForStartEnd(const std::string& rfilePath);
	void reset();//Reset the map to the original state

	void Update(float);
	void draw(sf::RenderWindow& window);

	void setTotalFrame(int rFrameNum) { totalFrame = rFrameNum; }
	void setTexture(const std::vector<sf::Texture>&);
	vector<vector<point>>& getMap_Game() {
		return _Map_Game_Logic;
	}
};

