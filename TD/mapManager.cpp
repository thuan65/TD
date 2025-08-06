#include "mapManager.h"
#include "WaveManager.h" //For 
#include "BulletManager.h"
#include "mapTowerDefense_Game.h"
#include "TowerManager.h"
#include <fstream>


mapManager::mapManager(mapTowerDefense_Game* rgameMap, BulletManager* rbulletManager, WaveManager* rwaveControl, TowerManager* rtowerControl, PlayState mapSelection) // cjamge rmapSelection dataType later
	:gameMap(rgameMap), bulletManager(rbulletManager), waveControl(rwaveControl), towerControl(rtowerControl), mapSelection(mapSelection)
{

}

void mapManager::selectMap(PlayState rmapSelection) {//Already choose the map
	mapSelection = rmapSelection;

	switch (mapSelection) {
	case PlayState::Map1:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig1.txt"); break;
	}
	case PlayState::Map2:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig2.txt"); break;
	}
	case PlayState::Map3:
	{
		loadMapConfig("Data\\6mapSelection\\mapconfig3.txt");; break;
	}
	case PlayState::Map4:
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
// mapManager.cpp
void mapManager::loadMapConfig(std::string filePathMapconfg) {
	std::ifstream fin(filePathMapconfg);
	if (fin.fail()) {
		throw std::runtime_error("Cannot open map config file: " + filePathMapconfg);
	}

	std::string key;
	std::string value;

	// Đọc từng cặp key-value
	while (fin >> key >> value) {
		if (key == "wave_path") {
			mapcfg.filePathForEnemyWave = value;
		}
		else if (key == "map_texture") {
			mapcfg.mapName = value;
		}
		else if (key == "build_pos") {
			mapcfg.filePathForBuildPosition = value;
		}
	}

	// In ra để debug
	std::cout << "Loaded map config:" << std::endl;
	std::cout << " - Wave Path: " << mapcfg.filePathForEnemyWave << std::endl;
	std::cout << " - Map Texture: " << mapcfg.mapName << std::endl;
	std::cout << " - Build Positions: " << mapcfg.filePathForBuildPosition << std::endl;
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

