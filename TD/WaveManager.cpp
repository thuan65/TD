#include "WaveManager.h"
#include "enemy.h"

WaveManager::WaveManager()
	: filePath("No path for wave loading yet"), wave_number(1), enemySpawnIndex(0) //Start from wave 1
{
}

WaveManager::~WaveManager() {
	for (int i = 0; i < activeEnemy.size(); ++i) {
		delete activeEnemy[i];
		activeEnemy[i] = nullptr;
	}
	activeEnemy.clear();
}

void WaveManager::setFilePath(const std::string& rfilePath) {
	filePath = rfilePath;
}

void WaveManager::reset() {
	wave_number = 1;
	enemySpawnIndex = 0; 
	//clear all enemy from past game
	for (int i = 0; i < activeEnemy.size(); ++i) {
		delete activeEnemy[i];
		activeEnemy[i] = nullptr;
	}
	activeEnemy.clear();
	_enemyToRemove.clear();
}

void WaveManager::startNewWave() {
	// Nếu không phải là wave đầu tiên và wave cũ chưa kết thúc, thì không làm gì cả
	if (wave_number > 1 && !WaveEnded()) {
		return;
	}

	// Nếu đã hoàn thành tất cả các wave, cũng không làm gì cả
	if (wave_number > TOTAL_WAVES) { // TOTAL_WAVES là hằng số bạn đã thêm
		return;
	}

	// Nếu wave_number là 0 (lần đầu tiên) thì tăng lên 1
	if (wave_number == 0) {
		wave_number = 1;
	}

	enemySpawnIndex = 0;
	timeSinceLastWave = 0;
	loadWaveFromFile(wave_number); // Load wave hiện tại

	// Chỉ tăng wave_number để chuẩn bị cho lần gọi tiếp theo
	wave_number++;
}

void WaveManager::loadWaveFromFile(int rwave_number) {

	ifstream fin("Data\\1wave\\map1\\wave" + to_string(rwave_number) + ".txt");

	if (fin.fail()) {//use catch throw here
		cout << "ERROR Reading WaveSpawn File";
		return;
	}

	std::string line;
	EnemyInfoForWave.clear();
	while (getline(fin, line)) {
		if (line[0] == '#') continue;
		stringstream ss(line);

		EnemyInfo info;
		ss >> info.spawnTime;
		ss >> info.enemy_type;
		ss >> info.health;
		ss >> info.speed;
		ss >> info.bounty;

		EnemyInfoForWave.emplace_back(info);
	}
	fin.close();
}

void WaveManager::spawnEnemy(const EnemyInfo& info) {
	enemy* e = new enemy(Resource_Management::getTexture(info.enemy_type), PathFinder::getPath(), info.health, info.speed, info.bounty);
	activeEnemy.push_back(e);
}

bool WaveManager::AllEnemySpawned() const {
	if (enemySpawnIndex < EnemyInfoForWave.size()) return false;
	return true;
}

bool WaveManager::WaveEnded() {
	return activeEnemy.empty() && enemySpawnIndex >= EnemyInfoForWave.size();
}

void WaveManager::update(float deltaTime) {
	timeSinceLastWave += deltaTime;

	if (!AllEnemySpawned() && enemySpawnIndex < EnemyInfoForWave.size() && EnemyInfoForWave[enemySpawnIndex].spawnTime <= timeSinceLastWave) {
		spawnEnemy(EnemyInfoForWave[enemySpawnIndex]);
		enemySpawnIndex++;
	}

	if (activeEnemy.empty()) return;

	for (int i = activeEnemy.size() - 1; i >= 0; --i) {
		activeEnemy[i]->Update(deltaTime);

		if (!activeEnemy[i]->isEnemyAlive() || activeEnemy[i]->reachedEnd()) {
		
			_enemyToRemove.push_back(activeEnemy[i]);
	
		}

	}

}

void WaveManager::processRemovals(int* enemiesReachedEnd, int* moneyFromKills) {
	if (enemiesReachedEnd) *enemiesReachedEnd = 0;
	if (moneyFromKills) *moneyFromKills = 0;

	if (_enemyToRemove.empty()) return;

	for (enemy* toRemove : _enemyToRemove) {
		auto it = std::find(activeEnemy.begin(), activeEnemy.end(), toRemove);
		if (it != activeEnemy.end()) {
			enemy* foundEnemy = *it;
			if (foundEnemy->reachedEnd() && enemiesReachedEnd) {
				(*enemiesReachedEnd)++;
			}
			if (!foundEnemy->isEnemyAlive() && moneyFromKills) {
				int bounty = foundEnemy->getBounty();
				(*moneyFromKills) += bounty;
				// --- THÊM COUT Ở ĐÂY ---
				std::cout << "[WaveManager] Enemy killed! Bounty: " << bounty
					<< ". Total moneyFromKills so far: " << *moneyFromKills << std::endl;
			}
			delete foundEnemy;
			activeEnemy.erase(it);
		}
	}
	_enemyToRemove.clear();
}

void WaveManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < activeEnemy.size(); i++) {
		activeEnemy[i]->draw(window);
	}
}
