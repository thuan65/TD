#pragma once
#include "tool.h"
#include "enemy.h"
#include "tower.h"

class map{

private:
	enemy _e;
	tower _tw;

	//Matrix map
	point _m[point::MAP_SIZE][point::MAP_SIZE];

public:
	map();
	// -1 là tường, 0 là trống, 1 là tower
	void resetMapData();
	void makeMapData();
	void drawMap();

	enemy& getEnemy() { return _e; }
	tower& getTower() { return _tw; }

};

