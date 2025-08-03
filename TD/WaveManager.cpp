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

void WaveManager::startNewWave()
{
	if (!WaveEnded()) return; //if wave not end yet
	enemySpawnIndex = 0;
	timeSinceLastWave = 0;
	loadWaveFromFile(wave_number);
	wave_number++;
	if (wave_number + 1 > EnemyInfo::TOTAL_WAVES) { // Fixed TOTAL_WAVES reference
		// Nếu muốn, xóa dòng này đi để nó không báo lỗi nữa
		// cout << "All waves completed!" << endl;
		return;
	}
}

void WaveManager::loadWaveFromFile(int rwave_number) {

	ifstream fin(filePath + to_string(rwave_number) + ".txt");
	try {
		if (fin.fail()) {//use catch throw here
		throw std::runtime_error("ERROR Reading WaveSpawn File");
	}
	}
	catch (const std::runtime_error& e) {
		// In lỗi ra console và ném lại để chương trình có thể dừng lại
		std::cerr << "Resource loading failed: " << e.what() << std::endl;
		throw;
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
	enemy* e = new enemy(Resource_Management::getTexture(info.enemy_type), PathFinder::getPath(), info.health, info.speed);
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
	// Reset các biến đếm
	if (enemiesReachedEnd) *enemiesReachedEnd = 0;
	if (moneyFromKills) *moneyFromKills = 0;

	if (!_enemyToRemove.empty()) {
		auto it = _enemyToRemove.begin();
		while (it != _enemyToRemove.end()) {
			enemy* toRemove = *it;

			// Tìm và xóa khỏi activeEnemy
			for (auto activeIt = activeEnemy.begin(); activeIt != activeEnemy.end(); ) {
				if (*activeIt == toRemove) {
					// Kiểm tra lý do bị xóa
					if (toRemove->reachedEnd() && enemiesReachedEnd) {
						(*enemiesReachedEnd)++;
					}
					if (!toRemove->isEnemyAlive() && moneyFromKills) {
						// (*moneyFromKills) += toRemove->getBounty(); // Cần thêm hàm getBounty() cho enemy
					}

					delete* activeIt;
					activeIt = activeEnemy.erase(activeIt); // Xóa và lấy iterator tiếp theo
					goto next_removal; // Nhảy đến lần lặp tiếp theo của vòng lặp ngoài
				}
				else {
					++activeIt;
				}
			}
		next_removal:
			it = _enemyToRemove.erase(it);
		}
	}
}

void WaveManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < activeEnemy.size(); i++) {
		activeEnemy[i]->draw(window);
	}
}
