#include "mapManager.h"
#include "WaveManager.h" //For 
#include "BulletManager.h"
#include "mapTowerDefense_Game.h"
#include "TowerManager.h"
#include "Resource_Management.h"

mapManager::mapManager(mapTowerDefense_Game* rgameMap, BulletManager* rbulletManager, WaveManager* rwaveControl, TowerManager* rtowerControl, int rmapSelection) // cjamge rmapSelection dataType later
	:gameMap(rgameMap), bulletManager(rbulletManager), waveControl(rwaveControl), towerControl(rtowerControl), mapSelection(rmapSelection)
{
}

void mapManager::selectMap(int rmapSelection) {//Add arguement later

	if (rmapSelection == 1) {
		loadMapConfig("Data\\6mapSelection\\mapconfig1.txt");
	}
	if (rmapSelection == 2) {

	}
	if (rmapSelection == 3) {

	}
	if (rmapSelection == 4) {

	}
	//add a exception catch error here

	setMap();
}

void mapManager::loadMapConfig(std::string filePathMapconfg) {
	std::ifstream fin(filePathMapconfg);
	//put a throw catch here later (fin.fail())

		std::string line;
		std::getline(fin, line);
		mapcfg.filePathForEnemyWave = line;
		std::getline(fin, line);
		mapcfg.mapName = line;


}

void mapManager::setMap() {
	waveControl->setFilePath(mapcfg.filePathForEnemyWave);
	gameMap->setTexture(Resource_Management::getTexture(mapcfg.mapName));
}

