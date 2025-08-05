#include "TowerManager.h"

TowerManager::TowerManager(sf::RenderWindow* window, BulletManager* rbulletManager)
	: window(window), bulletManager(rbulletManager), isBuildMenuOpen(false)
{
	setupBuildMenu();
}

TowerManager::~TowerManager() {
	for (int i = 0; i < towers.size(); ++i) {
		delete towers[i];
		towers[i] = nullptr;
	}
	towers.clear();
}

void TowerManager::setupBuildMenu() {
	buildMenuBackground = std::make_unique<sf::RectangleShape>();
	buildMenuBackground->setSize({ 148.f, 60.f });
	buildMenuBackground->setFillColor(sf::Color(100, 100, 100, 200));

	buildMenuTower1Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower1_Icon")[0]);
	buildMenuTower2Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower2_Icon")[0]);
	buildMenuTower3Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower3_Icon")[0]);
	buildMenuTower4Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower4_Icon")[0]);
}

void TowerManager::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
	sprite_vector.clear();
	std::string numStr = std::to_string(number);
	float currentX = x;
	const float digitScale = 0.015f; // Chỉnh size số
	for (char c : numStr) {
		int digit = c - '0';
		const sf::Texture& tex = Resource_Management::Digits[digit][0];
		sf::Sprite sprite(tex);
        sprite.setScale(sf::Vector2f(digitScale, digitScale));
		sprite.setPosition({ currentX, y });
		sprite_vector.push_back(sprite);
		currentX += tex.getSize().x * digitScale;
	}
}




void TowerManager::openBuildMenu(int row, int col) {
	isBuildMenuOpen = true;
	buildMenuTilePosition = { col, row }; // Gán vị trí ô đất (x=col, y=row)

	// --- TÍNH TOÁN LẠI VỊ TRÍ MENU ---

	// 1. Lấy tọa độ tâm của ô đất đã click
	float tileCenterX = static_cast<float>(col * point::TileSize) + (point::TileSize / 2.f);
	float tileCenterY = static_cast<float>(row * point::TileSize) + (point::TileSize / 2.f);

	// 2. Lấy kích thước của nền menu
	sf::Vector2f menuSize = buildMenuBackground->getSize();

	// 3. Tính toán vị trí góc trên-trái của menu để nó được CĂN GIỮA
	// so với tâm ô đất và nằm ngay PHÍA TRÊN ô đất
	float menuX = tileCenterX - (menuSize.x / 2.f);
	float menuY = tileCenterY - (point::TileSize / 2.f) - menuSize.y - 5.f; // 5.f là khoảng đệm

	// Đảm bảo menu không bị vẽ ra ngoài màn hình
	const sf::Vector2u windowSize = window->getSize();
	if (menuX < 0) menuX = 0;
	if (menuY < 0) menuY = 0;
	if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
	if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;


	// 4. Đặt vị trí cho nền và các icon
	buildMenuBackground->setPosition(sf::Vector2f(menuX, menuY));

	// Vị trí các icon được tính dựa trên vị trí mới của menu
	buildMenuTower1Icon->setPosition(sf::Vector2f(menuX + 5.f, menuY + 2.5f));
	buildMenuTower2Icon->setPosition(sf::Vector2f(menuX + 42.f, menuY + 2.5f));
	buildMenuTower3Icon->setPosition(sf::Vector2f(menuX + 79.f, menuY + 2.5f));
	buildMenuTower4Icon->setPosition(sf::Vector2f(menuX + 116.f, menuY + 2.5f));

	// Cập nhật lại vùng clickable
   /* tower1IconBounds = buildMenuTower1Icon->getGlobalBounds();
	tower2IconBounds = buildMenuTower2Icon->getGlobalBounds();
	tower3IconBounds = buildMenuTower3Icon->getGlobalBounds();
	tower4IconBounds = buildMenuTower4Icon->getGlobalBounds();*/

	drawNumber(TOWER1_COST, buildMenuTower1Icon->getPosition().x, buildMenuTower1Icon->getPosition().y + 50, tower1CostSprites);
	drawNumber(TOWER2_COST, buildMenuTower2Icon->getPosition().x, buildMenuTower2Icon->getPosition().y + 50, tower2CostSprites);
	drawNumber(TOWER3_COST, buildMenuTower3Icon->getPosition().x, buildMenuTower3Icon->getPosition().y + 50, tower3CostSprites);
	drawNumber(TOWER4_COST, buildMenuTower4Icon->getPosition().x, buildMenuTower4Icon->getPosition().y + 50, tower4CostSprites);

}





void TowerManager::closeBuildMenu() {
	isBuildMenuOpen = false;
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

bool TowerManager::towerTowerExisted(const buildZone& zone) {
	return zone.TowerExist;
}

void TowerManager::ReadFile(const std::string& filePath) {
	std::ifstream fin(filePath);
	if (fin.fail()) {
		throw std::runtime_error("Fail to open build_Position.txt");
	}

	buildZones.clear(); // Xóa các zone cũ
	float row, col;
	std::string ignoreline;
	getline(fin, ignoreline);

	while (fin >> row >> col) {
		sf::FloatRect zone(sf::Vector2f{ col * point::TileSize, row * point::TileSize }, sf::Vector2f{ point::TileSize, point::TileSize } *1.5F);

		zone.position = zone.position - (zone.size / 2.0F); // To center the box
		buildZones.push_back(buildZone({ zone, false })); //Gồm vòng spaw tháp và có Tháp hay không
	}
	//std::cout << buildZones[1].bounds.position.x << " " << buildZones[1].bounds.position.y << "\n";
}

bool TowerManager::buildTower(sf::Vector2f worldPos, std::string towerType) {
	tower* buildNewTower = new tower(Resource_Management::getTexture(towerType));
	for (int i = 0; i < buildZones.size(); ++i) {//Tìm ô có thể xây tháp

		if (buildZones[i].bounds.contains(worldPos)) {
			buildNewTower->setPosition(buildZones[i].bounds.getCenter());//Set the tower position in the middle of the Tile
			buildZones[i].TowerExist = true;
			//std::cout << "Build:  " << buildZones[i].bounds.getCenter().x << " " << buildZones[i].bounds.getCenter().y << "\n";
			//std::cout << buildNewTower->getPosition().x << " " << buildNewTower->getPosition().y << "\n";
			towers.emplace_back(buildNewTower);
			return true;
			break;
		}
	}
}


void TowerManager::resolveTowerAt(sf::Vector2f worldPos, int& money) {
	//std::cout << worldPos.x << " " << worldPos.y << "\n";

	if (towerTowerExisted(worldPos)) {
		return;//If the tower exist do sth(sell, upgrate)

	}

	else {//There is no tower in this Build Zone
		if (isBuildMenuOpen) {
			// TÍNH TOÁN BOUNDS NGAY TẠI ĐÂY
			if (buildMenuTower1Icon->getGlobalBounds().contains(worldPos)) {
				if (money >= TOWER1_COST) {
					money -= TOWER1_COST;
					buildTower(theTowerPosition, "Tower1");

				}
				closeBuildMenu();
			}
			else if (buildMenuTower2Icon->getGlobalBounds().contains(worldPos)) {
				if (money >= TOWER2_COST) {
					money -= TOWER2_COST;
					buildTower(theTowerPosition, "Tower2");
				}

				closeBuildMenu();
			}
			else if (buildMenuTower3Icon->getGlobalBounds().contains(worldPos)) {
				if (money >= TOWER3_COST) {
					money -= TOWER3_COST;
					buildTower(theTowerPosition, "Tower3");
				}

				closeBuildMenu();
			}
			else if (buildMenuTower4Icon->getGlobalBounds().contains(worldPos)) {
				if (money >= TOWER4_COST) {
					money -= TOWER4_COST;
					buildTower(theTowerPosition, "Tower4");

				}

				closeBuildMenu();
			}
			else {
				closeBuildMenu();
			}
		}
		else {
			int row = static_cast<int>(worldPos.y / point::TileSize);
			int col = static_cast<int>(worldPos.x / point::TileSize);
			if (clickCheck(worldPos)) {//Check to see if there is a BuildZone here (Tile that can build tower)
				openBuildMenu(row, col);
				theTowerPosition = worldPos;//Save the Placing Position for Tower
			}
		}
	}

}

bool TowerManager::clickCheck(sf::Vector2f worldPos) {
	for (int i = 0; i < buildZones.size(); ++i) {//Check all the Building Tile avaiable
		if (buildZones[i].bounds.contains(worldPos)) {
			return true;//If there are return true
		}
	}
	return false;//No Building tile here
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

	if (isBuildMenuOpen) {
		if (buildMenuBackground) window.draw(*buildMenuBackground);
		if (buildMenuTower1Icon) window.draw(*buildMenuTower1Icon);
		if (buildMenuTower2Icon) window.draw(*buildMenuTower2Icon);
		if (buildMenuTower3Icon) window.draw(*buildMenuTower3Icon);
		if (buildMenuTower4Icon) window.draw(*buildMenuTower4Icon);


		for (const auto& s : tower1CostSprites) window.draw(s);
		for (const auto& s : tower2CostSprites) window.draw(s);
		for (const auto& s : tower3CostSprites) window.draw(s);
		for (const auto& s : tower4CostSprites) window.draw(s);


	}

	//for (const auto& zone : buildZones) {
	//sf::RectangleShape shape;
	//shape.setPosition(sf::Vector2f(zone.bounds.position));
	//shape.setSize(sf::Vector2f(zone.bounds.size));
	//shape.setFillColor(sf::Color::Transparent);
	//shape.setOutlineColor(sf::Color::Green);
	//shape.setOutlineThickness(1.f);
	//window.draw(shape);
	//}

}


