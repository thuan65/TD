#pragma once
#include <iostream> // this is for debbug
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
	int wave_number; 
	int enemySpawnIndex;
	float timeSinceLastWave;

public:
	WaveManager();

	void startNewWave();
	bool AllEnemySpawned() const;
	void loadWaveFromFile(int rwave_number);
	void spawnEnemy(const EnemyInfo& info);
	void update(float deltaTime); //Update in wave (spawn enemy and update enemy)
	void draw(sf::RenderWindow& window);

	bool WaveEnded();


};

