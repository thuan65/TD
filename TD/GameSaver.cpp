//#include "GameSaver.h"
//#include "mapManager.h"
//#include "WaveManager.h"
//
//
//GameSaver::GameSaver(game* cgame)
//	: cgame(cgame)
//{
//}
//
//void GameSaver::saveGame(const string& filePath) {
//
//	mapManager mapSelection = cgame->getMapManager();
//	std::string mapNumber;//Chon 1 map trong 4 map
//	WaveManager& waveControl = cgame->getWaveManager();
//
//	std::ofstream fout(filePath);
//	if (fout.fail()) {
//		throw std::runtime_error("Cannot Save Game");
//	}
//
//	PlayState mapSelectionNumber = mapSelection.getMapSelection();
//	if (mapSelectionNumber == PlayState::Map1) {
//		mapNumber = "Map1";
//	}
//	else if (mapSelectionNumber == PlayState::Map2) {
//		mapNumber = "Map2";
//	}
//	else if (mapSelectionNumber == PlayState::Map3) {
//		mapNumber = "Map3";
//	}
//	else if (mapSelectionNumber == PlayState::Map4) {
//		mapNumber = "Map4";
//	}
//
//	fout << mapNumber << "\n";
//	fout << "Lives " << cgame->getLives() << "\n";
//	fout << "Gold " << cgame->getMoney() << "\n";
//	fout << "CurrentWave " << cgame->getCurrentWave() << "\n";
//	fout << "isGameOver " << cgame->getIsGameOver() << "\n";
//	fout << "PlayerWon " << cgame->getPlayerWon() << "\n";
//
//	fout << "wave_number " << waveControl.getWaveNumber() << "\n";
//	fout << "enemySpawnIndex " << waveControl.getEnemySpawnIndex() << "\n";
//	fout << "timeSinceLastWave " << waveControl.getTimeSinceLastWave() << "\n";
//
//
//	std::vector<enemy*> activeEnemy = waveControl.getActiveEnemy();
//
//	for (int i = 0; i < activeEnemy.size(); ++i) {
//		fout << *activeEnemy[i] << " ";
//	}
//	fout.close();
//}
//
//void GameSaver::loadGame(const string& filePath) {
//
//
//
//}
