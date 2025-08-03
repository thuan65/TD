#pragma once
#include <string>
#include <fstream>

class mapTowerDefense_Game;
class BulletManager;
class WaveManager;
class TowerManager;

class mapManager {
public:
	mapManager(mapTowerDefense_Game* rgameMap, BulletManager* rbulletManager, WaveManager* rwaveControl, TowerManager* rtowerControl , int rmapSelection = 1);

	void selectMap(int rmapSelection);//Give arguement a dataType
	void loadMapConfig(std::string filePathMapconfg);
	void setMap();

private:

	mapTowerDefense_Game* gameMap;
	BulletManager* bulletManager;
	WaveManager* waveControl;
	TowerManager* towerControl;

	int mapSelection;

	struct mapConfig{
		std::string filePathForEnemyWave;
		std::string mapName;
		std::string filePathForBuildPosition;
	};

	mapConfig mapcfg;

};

