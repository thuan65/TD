#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "enemy.h"
#include "Resource_Management.h"
#include "PathFinder.h"

class WaveManager {

private:

	struct EnemyInfo {
		float spawnTime;
		std::string enemy_type;
		int health;
		int speed;
	};

	std::vector <EnemyInfo> EnemyInfoForWave;
	std::vector<enemy*> activeEnemy;
	int enemySpawnIndex = 0;
	float timeSinceLastWave;

public:
	WaveManager();

	void startNewWave();
	bool IsAllEnemySpawned() const;
	void loadWaveFromFile();
	void spawnEnemy(const EnemyInfo& info);
	void update(float deltaTime, sf::RenderWindow& window); //Update in wave (spawn enemy and update enemy)



};

