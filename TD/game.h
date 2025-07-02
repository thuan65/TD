#pragma once
#include "mapTowerDefense_Game.h"

#include "WaveManager.h"
#include "TowerManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Resource_Management.h"
#include "PathFinder.h"
#include <thread>
#include <iostream>

class game {
	
private:
	sf::RenderWindow window;
	mapTowerDefense_Game gameMap;


public:
	game();
	~game();

	void Run();

};

//class game {
//private:
//	Map_Game _Map_Game;
//	bool _ISEXIT1, _ISEXIT2;
//
//public:
//	game();
//
//	bool getIsExist1() { return _ISEXIT1; }
//	bool getIsExist2() { return _ISEXIT2; }
//	void setIsExist1(bool b) { _ISEXIT1 = b; }
//	void setIsExist2(bool b) { _ISEXIT2 = b; }
//	Map_Game& getMap_Game() { return _Map_Game; }
//	void startGame();
//};

