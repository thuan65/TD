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

bool TowerManager::towerTowerExisted(sf::Vector2f worldPos) {
	for (int i = 0; i < buildZones.size(); ++i) {
		if (buildZones[i].bounds.contains(worldPos)) {
			return buildZones[i].TowerExist;
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
		sf::FloatRect zone(sf::Vector2f{ col * point::TileSize, row * point::TileSize }, sf::Vector2f{ point::TileSize, point::TileSize } *1.5F);

		zone.position = zone.position - (zone.size / 2.0F); // To center the box
		buildZones.push_back(buildZone({zone, false})); //Gồm vòng spaw khác và có Tháp hay không
	}
	//std::cout << buildZones[1].bounds.position.x << " " << buildZones[1].bounds.position.y << "\n";
}

bool TowerManager::clickCheck(sf::Vector2f worldPos) {
	for (int i = 0; i < buildZones.size(); ++i) {
		if (buildZones[i].bounds.contains(worldPos)) {
			return true;
		}
	}
	return false;
}

void TowerManager::buildTower(sf::Vector2f worldPos, const std::string& towerType) {
	//std::cout << worldPos.x << " " << worldPos.y << "\n";

	if (towerTowerExisted(worldPos)) return;//If the tower exist do sth(sell, upgrate)
	else {//Build place is valid and no tower there yet
		tower* buildNewTower = new tower(Resource_Management::getTexture(towerType));
		for (int i = 0; i < buildZones.size(); ++i) {//Tìm ô có thể xây khác

			if (buildZones[i].bounds.contains(worldPos)) {
				buildNewTower->setPosition(buildZones[i].bounds.getCenter());
				buildZones[i].TowerExist = true;
				//std::cout << "Build:  " << buildZones[i].bounds.getCenter().x << " " << buildZones[i].bounds.getCenter().y << "\n";
				//std::cout << buildNewTower->getPosition().x << " " << buildNewTower->getPosition().y << "\n";
				towers.emplace_back(buildNewTower);
			
				break;
			}
		}
		}
	
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

	for (const auto& zone : buildZones) {
	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(zone.bounds.position));
	shape.setSize(sf::Vector2f(zone.bounds.size));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	window.draw(shape);
	}





}


