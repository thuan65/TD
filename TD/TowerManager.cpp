#include "TowerManager.h"

TowerManager::TowerManager(BulletManager* rbulletManager)
	: bulletManager(rbulletManager)
{}



TowerManager::~TowerManager() {
	for (int i = 0; i < towers.size(); ++i) {
		delete towers[i];
		towers[i] = nullptr;
	}
	towers.clear();
}



void TowerManager::update(float deltaTime, std::vector<enemy*>& enemies) {
	for (int i = 0; i < towers.size(); ++i) {
		towers[i]->update(deltaTime, enemies, bulletManager);	
	}
}

bool TowerManager::towerTowerExisted(int row, int col) {
	if (towers.empty()) {
		return false;
	}
	for (int i = 0; i < towers.size(); ++i) {
		if (towers[i]->getRow() == row && towers[i]->getCol() == col) {
			return true;
		}
	}
	return false;
}

void TowerManager::buildTower(int row, int col, const std::string& towerType) {
	if (towerTowerExisted(row, col)) return;
	tower* buildNewTower = new tower(Resource_Management::getTexture(towerType), row, col);
	towers.emplace_back(buildNewTower);
}
void TowerManager::sellTower() {

}

void TowerManager::upgrateTower() 
{
}

void TowerManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < towers.size(); ++i) {
		towers[i]->draw(window);
	}
}

