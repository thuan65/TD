#pragma once
#include <iostream> // this is for debbug
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "enemy.h"
#include "Resource_Management.h"
#include "PathFinder.h"
#include "ISaveable.h"

struct RemovalResult {//Sau khi xóa, kiểm tra có enemy nào về đích, hoặc bị kill
	int enemiesReachedEnd = 0;
	int moneyFromKills = 0;
};

class WaveManager : public ISaveable {

private:

	std::string filePath;

	struct EnemyInfo {
		float spawnTime;
		std::string enemy_type;
		int health;
		int speed;
		int bounty;
		static const int TOTAL_WAVES = 3; // << TONG WAVE LA 3	
	};

	std::vector <EnemyInfo> EnemyInfoForWave;
	std::vector<enemy*> activeEnemy;
	int wave_number;//The number of wave of a map
	int enemySpawnIndex;
	float timeSinceLastWave;
	std::vector<enemy*> _enemyToRemove;

public:
	static const int TOTAL_WAVES = 3; // << THÊM DÒNG NÀY
	WaveManager();
	~WaveManager();

	std::vector<enemy*>& getActiveEnemy() { return activeEnemy; }
	void setFilePath(const std::string& rfilePath);
	void reset();//To reset the wave (use in after select map or load save game)
	void addEnemy(enemy* renemy);

	void setWaveNumber(int rwave_number) { wave_number = rwave_number; }
	void setEnemySpawnIndex(int rEnemySpawnIndex) { enemySpawnIndex = rEnemySpawnIndex; }
	void setTimeSinceLastWave(float rtimeSinceLastWave) { timeSinceLastWave = rtimeSinceLastWave; }

	int getWaveNumber() { return wave_number; }
	int getEnemySpawnIndex() { return enemySpawnIndex; }
	float getTimeSinceLastWave() { return timeSinceLastWave; }

	void startWave(int waveNum);
	void startNewWave();
	bool AllEnemySpawned() const;
	void loadWaveFromFile(int rwave_number);//Load Enemy Info For Wave everytime a new wave start
	void spawnEnemy(const EnemyInfo& info);//Spawn enemy by read it in the EnemyInfoForWave
	void update(float deltaTime); //Update in wave (spawn enemy and update enemy)
	RemovalResult processRemovals();
	void draw(sf::RenderWindow& window);

	bool WaveEnded();

	//Logic cho save file
	void save(std::ostream& fileOut) const override;
	void loadSave(std::istream& fileOut) override;

};

