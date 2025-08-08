#pragma once
#include <string>
#include <fstream>
#include "gameSate.h"
#include "Resource_Management.h"

class mapTowerDefense_Game;
class BulletManager;
class WaveManager;
class TowerManager;

class mapManager {
public:
	mapManager(mapTowerDefense_Game* rgameMap, BulletManager* rbulletManager, WaveManager* rwaveControl, TowerManager* rtowerControl, MapID mapSelection = MapID::Map1);//For debug map 1 is default

	void selectMap(MapID rmapSelection);//Give arguement a dataType
	void loadMapConfig(std::string filePathMapconfg);
	void setUpMap();
	
	MapID getMapSelection() { return mapSelection; }

private:

	mapTowerDefense_Game* gameMap;
	BulletManager* bulletManager;
	WaveManager* waveControl;
	TowerManager* towerControl;

	MapID mapSelection;

	struct mapConfig{
		std::string filePathForEnemyWave;
		std::string mapName;
		std::string filePathForMapLogic;
		std::string filePathForStartEndPositon;
		std::string filePathForBuildPosition;
	};

	mapConfig mapcfg;

};

