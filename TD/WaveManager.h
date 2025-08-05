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

	std::string filePath;

	struct EnemyInfo {
		float spawnTime;
		std::string enemy_type;
		int health;
		int speed;
		int bounty;
		static const int TOTAL_WAVES = 10; // << TONG WAVE LA 3	
	};

	std::vector <EnemyInfo> EnemyInfoForWave;
	std::vector<enemy*> activeEnemy;
	int wave_number;
	int enemySpawnIndex;
	float timeSinceLastWave;
	std::vector<enemy*> _enemyToRemove;

public:
	static const int TOTAL_WAVES = 10; // << THÊM DÒNG NÀY
	WaveManager();
	~WaveManager();

	std::vector<enemy*>& getActiveEnemy() { return activeEnemy; }
	void setFilePath(const std::string& rfilePath);
	void reset();//To reset the wave (use in after select map or load save game)
	void startNewWave();
	bool AllEnemySpawned() const;
	void loadWaveFromFile(int rwave_number);//Load Enemy Info For Wave everytime a new wave start
	void spawnEnemy(const EnemyInfo& info);//Spawn enemy by read it in the EnemyInfoForWave
	void update(float deltaTime); //Update in wave (spawn enemy and update enemy)
	void processRemovals(int* enemiesReachedEnd, int* moneyFromKills);
	void draw(sf::RenderWindow& window);

	bool WaveEnded();
};

