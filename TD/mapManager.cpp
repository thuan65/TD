#include "mapManager.h"
#include "WaveManager.h" //For 
#include "BulletManager.h"
#include "mapTowerDefense_Game.h"
#include "TowerManager.h"


mapManager::mapManager(mapTowerDefense_Game* rgameMap, BulletManager* rbulletManager, WaveManager* rwaveControl, TowerManager* rtowerControl, MapID mapSelection)
	:gameMap(rgameMap), bulletManager(rbulletManager), waveControl(rwaveControl), towerControl(rtowerControl), mapSelection(mapSelection)
{
}

void mapManager::selectMap(MapID rmapSelection) {//Already choose the map
	mapSelection = rmapSelection;

	switch (mapSelection) {
	case MapID::Map1:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig1.txt"); break;
	}
	case MapID::Map2:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig2.txt"); break;	
	}
	case MapID::Map3:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig3.txt");; break;
	}
	case MapID::Map4:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig4.txt"); break;
	}
	default:
	{
		throw std::invalid_argument("Cannot load Map config");
	}
	}

	setUpMap();//Set up everything about the map ... reset everything
}

void mapManager::loadMapConfig(std::string filePathMapconfg) {
	std::ifstream fin(filePathMapconfg);
	if (fin.fail()) {
		throw std::invalid_argument("Cannot open file Map config");
	}
	

		std::string line;
		std::getline(fin, line);
		mapcfg.filePathForEnemyWave = line;

		std::getline(fin, line);
		mapcfg.mapName = line;

		std::getline(fin, line);
		mapcfg.filePathForMapLogic = line;

		std::getline(fin, line);
		mapcfg.filePathForStartEndPositon = line;

		std::getline(fin, line);
		mapcfg.filePathForBuildPosition = line;

}

void mapManager::setUpMap() {
	waveControl->setFilePath(mapcfg.filePathForEnemyWave);
	gameMap->setTexture(Resource_Management::getTexture(mapcfg.mapName));
	gameMap->setFilePath(mapcfg.filePathForMapLogic);
	
	gameMap->setFilePathForStartEnd(mapcfg.filePathForStartEndPositon);
	towerControl->ReadFile(mapcfg.filePathForBuildPosition);

	waveControl->reset();
	gameMap->reset();
	towerControl->reset();
}

