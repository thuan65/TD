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

void TowerManager::ReadFile(const std::string& filePath) {
	std::ifstream fin(filePath);
	if (fin.fail()) {
		throw std::runtime_error("Fail to open build_Position.txt");
	}

	float row, col;
	std::string ignoreline;
	getline(fin, ignoreline);

	while (fin >> row >> col) {
		sf::FloatRect zone(sf::Vector2f{col * point::TileSize, row * point::TileSize}, sf::Vector2f{point::TileSize, point::TileSize} * 1.5F);
	
		zone.position = zone.position - (zone.size / 2.0F); // To center the box

		buildZone.push_back(zone);
	}
}

bool TowerManager::clickCheck(sf::Vector2f worldPos) {
	for (int i = 0; i < buildZone.size(); ++i) {
		if (buildZone[i].contains(worldPos)) {
			return true;
		}
	}
	return false;
}

void TowerManager::buildTower(int row, int col, const std::string& towerType) {
	if (towerTowerExisted(row, col)) return;
	tower* buildNewTower = new tower(Resource_Management::getTexture(towerType), row, col);

	for (int i = 0; i < buildZone.size(); ++i) {
		if (buildZone[i].contains(sf::Vector2f{ (float)col * point::TileSize, (float)row * point::TileSize })) {
			buildNewTower->setPosition(buildZone[i].getCenter());
			break;
		}
	}


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

//for (const auto& zone : buildZone) {
//	sf::RectangleShape shape;
//	shape.setPosition(sf::Vector2f(zone.position));
//	shape.setSize(sf::Vector2f(zone.size));
//	shape.setFillColor(sf::Color::Transparent);
//	shape.setOutlineColor(sf::Color::Green);
//	shape.setOutlineThickness(1.f);
//
	//	window.draw(shape);
	//}

