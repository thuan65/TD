#include "WaveManager.h"

WaveManager::WaveManager() 
	: timeSinceLastWave(0)
{
	loadWaveFromFile();
}

void WaveManager::startNewWave()
{
}

bool WaveManager::IsAllEnemySpawned() const {
	if (enemySpawnIndex < EnemyInfoForWave.size()) return false;
	return true;
}

void WaveManager::loadWaveFromFile()
{
	ifstream fin("Data\\1wave\\map1\\wave1.txt");

	if (fin.fail()) {//use catch throw here
		cout << "ERROR Reading WaveSpawn File";
		return;
	}

	std::string line;

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
	enemy* e = new enemy(Resource_Management::getTexture(info.enemy_type), PathFinder::getPath(), info.speed);
	activeEnemy.push_back(e);
}

void WaveManager::update(float deltaTime, sf::RenderWindow& window) {
	timeSinceLastWave += deltaTime;
	
	if (enemySpawnIndex < EnemyInfoForWave.size() && EnemyInfoForWave[enemySpawnIndex].spawnTime <= timeSinceLastWave) {
		spawnEnemy(EnemyInfoForWave[enemySpawnIndex]);
		enemySpawnIndex++;
	}

	for (int i = 0; i < activeEnemy.size(); i++) {
		activeEnemy[i]->Update(deltaTime, window);
	}

}
