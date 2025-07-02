#include "TowerManager.h"

TowerManager::~TowerManager() {
	for (int i = 0; i < towers.size(); ++i) {
		delete towers[i];
		towers[i] = nullptr;
	}
}

void TowerManager::buildTower(int row, int col) {
	tower* buildNewTower = new tower(Resource_Management::getTexture("Sleame"), row, col);
	towers.emplace_back(buildNewTower);
}

void TowerManager::sellTower()
{
}

void TowerManager::upgrateTower()
{
}

void TowerManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < towers.size(); ++i) {
		towers[i]->draw(window);
	}
}

