#include "WaveManager.h"

WaveManager::WaveManager() 
	: wave_number(1) //Start from wave 1
{
}

WaveManager::~WaveManager() {
	for (int i = 0; i < activeEnemy.size(); ++i) {
		delete activeEnemy[i];
		activeEnemy[i] = nullptr;
	}
	activeEnemy.clear();
}

void WaveManager::startNewWave()
{
	if (!WaveEnded()) return; //if wave not end yet
	enemySpawnIndex = 0;
	timeSinceLastWave = 0;
	loadWaveFromFile(wave_number);
	wave_number++;
}

void WaveManager::loadWaveFromFile(int rwave_number)
{

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

		EnemyInfoForWave.emplace_back(info);
	}
		fin.close();
}

void WaveManager::spawnEnemy(const EnemyInfo& info) {
	enemy* e = new enemy(Resource_Management::getTexture(info.enemy_type), PathFinder::getPath(), info.speed, info.health);
	activeEnemy.push_back(e);
}

bool WaveManager::AllEnemySpawned() const {
	if (enemySpawnIndex < EnemyInfoForWave.size()) return false;
	return true;
}

bool WaveManager::WaveEnded()
{
	return activeEnemy.empty() && enemySpawnIndex >= EnemyInfoForWave.size();
}

void WaveManager::update(float deltaTime) {
	timeSinceLastWave += deltaTime;
	
	if (!AllEnemySpawned() && EnemyInfoForWave[enemySpawnIndex].spawnTime <= timeSinceLastWave) {
		spawnEnemy(EnemyInfoForWave[enemySpawnIndex]);
		enemySpawnIndex++;
	}

	if (activeEnemy.empty()) return; //If there is no enemy active now return

	for (int i = activeEnemy.size() - 1; i >= 0; --i) {
		activeEnemy[i]->Update(deltaTime);
		//std::cout << i << " ";

		if (!activeEnemy[i]->isEnemyAlive()) {//Enemy is unalive
			_enemyToRemove.push_back(activeEnemy[i]);
		}

		if (activeEnemy[i]->reachedEnd()) {
			_enemyToRemove.push_back(activeEnemy[i]);
		}
	}
	processRemovals();
}

void WaveManager::processRemovals() {
	if (!_enemyToRemove.empty()) {
		while (!_enemyToRemove.empty()) {
			enemy* target = _enemyToRemove.back();
			int tmp = -1;

			for (int i = 0; i < activeEnemy.size(); ++i) {
				if (target == activeEnemy[i]) {
					tmp = i;
					break;
				}
			}

			if (tmp == -1) continue;

			delete activeEnemy[tmp];
			activeEnemy.erase(activeEnemy.begin() + tmp);
			_enemyToRemove.pop_back();
		}
	}
}

void WaveManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < activeEnemy.size(); i++) {
		activeEnemy[i]->draw(window);
	}
}


