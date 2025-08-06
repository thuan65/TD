//#include "TowerManager.h"
//
//TowerManager::TowerManager(sf::RenderWindow* window, BulletManager* rbulletManager)
//	: window(window), bulletManager(rbulletManager), isBuildMenuOpen(false)
//{
//	setupBuildMenu();
//}
//
//TowerManager::~TowerManager() {
//	for (int i = 0; i < towers.size(); ++i) {
//		delete towers[i];
//		towers[i] = nullptr;
//	}
//	towers.clear();
//}
//
//void TowerManager::setupBuildMenu() {
//	buildMenuBackground = std::make_unique<sf::RectangleShape>();
//	buildMenuBackground->setSize({ 148.f, 60.f });
//	buildMenuBackground->setFillColor(sf::Color(100, 100, 100, 200));
//
//	buildMenuTower1Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower1_Icon")[0]);
//	buildMenuTower2Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower2_Icon")[0]);
//	buildMenuTower3Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower3_Icon")[0]);
//	buildMenuTower4Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower4_Icon")[0]);
//}
//
//void TowerManager::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
//	sprite_vector.clear();
//	std::string numStr = std::to_string(number);
//	float currentX = x;
//	const float digitScale = 0.015f; // Chỉnh size số
//	for (char c : numStr) {
//		int digit = c - '0';
//		const sf::Texture& tex = Resource_Management::Digits[digit][0];
//		sf::Sprite sprite(tex);
//        sprite.setScale(sf::Vector2f(digitScale, digitScale));
//		sprite.setPosition({ currentX, y });
//		sprite_vector.push_back(sprite);
//		currentX += tex.getSize().x * digitScale;
//	}
//}
//
//
//
//
//void TowerManager::openBuildMenu(int row, int col) {
//	isBuildMenuOpen = true;
//	buildMenuTilePosition = { col, row }; // Gán vị trí ô đất (x=col, y=row)
//
//	// --- TÍNH TOÁN LẠI VỊ TRÍ MENU ---
//
//	// 1. Lấy tọa độ tâm của ô đất đã click
//	float tileCenterX = static_cast<float>(col * point::TileSize) + (point::TileSize / 2.f);
//	float tileCenterY = static_cast<float>(row * point::TileSize) + (point::TileSize / 2.f);
//
//	// 2. Lấy kích thước của nền menu
//	sf::Vector2f menuSize = buildMenuBackground->getSize();
//
//	// 3. Tính toán vị trí góc trên-trái của menu để nó được CĂN GIỮA
//	// so với tâm ô đất và nằm ngay PHÍA TRÊN ô đất
//	float menuX = tileCenterX - (menuSize.x / 2.f);
//	float menuY = tileCenterY - (point::TileSize / 2.f) - menuSize.y - 5.f; // 5.f là khoảng đệm
//
//	// Đảm bảo menu không bị vẽ ra ngoài màn hình
//	const sf::Vector2u windowSize = window->getSize();
//	if (menuX < 0) menuX = 0;
//	if (menuY < 0) menuY = 0;
//	if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
//	if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;
//
//
//	// 4. Đặt vị trí cho nền và các icon
//	buildMenuBackground->setPosition(sf::Vector2f(menuX, menuY));
//
//	// Vị trí các icon được tính dựa trên vị trí mới của menu
//	buildMenuTower1Icon->setPosition(sf::Vector2f(menuX + 5.f, menuY + 2.5f));
//	buildMenuTower2Icon->setPosition(sf::Vector2f(menuX + 42.f, menuY + 2.5f));
//	buildMenuTower3Icon->setPosition(sf::Vector2f(menuX + 79.f, menuY + 2.5f));
//	buildMenuTower4Icon->setPosition(sf::Vector2f(menuX + 116.f, menuY + 2.5f));
//
//	// Cập nhật lại vùng clickable
//   /* tower1IconBounds = buildMenuTower1Icon->getGlobalBounds();
//	tower2IconBounds = buildMenuTower2Icon->getGlobalBounds();
//	tower3IconBounds = buildMenuTower3Icon->getGlobalBounds();
//	tower4IconBounds = buildMenuTower4Icon->getGlobalBounds();*/
//
//	drawNumber(TOWER1_COST, buildMenuTower1Icon->getPosition().x, buildMenuTower1Icon->getPosition().y + 50, tower1CostSprites);
//	drawNumber(TOWER2_COST, buildMenuTower2Icon->getPosition().x, buildMenuTower2Icon->getPosition().y + 50, tower2CostSprites);
//	drawNumber(TOWER3_COST, buildMenuTower3Icon->getPosition().x, buildMenuTower3Icon->getPosition().y + 50, tower3CostSprites);
//	drawNumber(TOWER4_COST, buildMenuTower4Icon->getPosition().x, buildMenuTower4Icon->getPosition().y + 50, tower4CostSprites);
//
//}
//
//
//
//void TowerManager::reset() {
//	for (int i = 0; i < towers.size(); ++i) {
//		delete towers[i];
//		towers[i] = nullptr;
//	}
//	towers.clear();
//	closeBuildMenu();
//}
//
//void TowerManager::closeBuildMenu() {
//	isBuildMenuOpen = false;
//}
//
//
//void TowerManager::update(float deltaTime, std::vector<enemy*>& enemies) {
//	for (int i = 0; i < towers.size(); ++i) {
//		towers[i]->update(deltaTime, enemies, bulletManager);
//	}
//}
//
//bool TowerManager::towerTowerExisted(sf::Vector2f worldPos) {
//	for (int i = 0; i < buildZones.size(); ++i) {
//		if (buildZones[i].bounds.contains(worldPos)) {
//			return buildZones[i].TowerExist;
//		}
//	}
//	return false;
//}
//
//bool TowerManager::towerTowerExisted(const buildZone& zone) {
//	return zone.TowerExist;
//}
//
//void TowerManager::ReadFile(const std::string& filePath) {
//	std::ifstream fin(filePath);
//	if (fin.fail()) {
//		throw std::runtime_error("Fail to open build_Position.txt");
//	}
//
//	buildZones.clear(); // Xóa các zone cũ
//	float row, col;
//	std::string ignoreline;
//	getline(fin, ignoreline);
//
//	while (fin >> row >> col) {
//		sf::FloatRect zone(sf::Vector2f{ col * point::TileSize, row * point::TileSize }, sf::Vector2f{ point::TileSize, point::TileSize } *1.5F);
//
//		zone.position = zone.position - (zone.size / 2.0F); // To center the box
//		buildZones.push_back(buildZone({ zone, false })); //Gồm vòng spaw tháp và có Tháp hay không
//	}
//	//std::cout << buildZones[1].bounds.position.x << " " << buildZones[1].bounds.position.y << "\n";
//}
//
//bool TowerManager::buildTower(sf::Vector2f worldPos, std::string towerType) {
//	tower* buildNewTower = new tower(towerType, Resource_Management::getTexture(towerType));
//	for (int i = 0; i < buildZones.size(); ++i) {//Tìm ô có thể xây tháp
//
//		if (buildZones[i].bounds.contains(worldPos)) {
//			buildNewTower->setPosition(buildZones[i].bounds.getCenter());//Set the tower position in the middle of the Tile
//			buildZones[i].TowerExist = true;
//			//std::cout << "Build:  " << buildZones[i].bounds.getCenter().x << " " << buildZones[i].bounds.getCenter().y << "\n";
//			//std::cout << buildNewTower->getPosition().x << " " << buildNewTower->getPosition().y << "\n";
//			towers.emplace_back(buildNewTower);
//			return true;
//			break;
//		}
//	}
//}
//
//
//void TowerManager::resolveTowerAt(sf::Vector2f worldPos, int& money) {
//	//std::cout << worldPos.x << " " << worldPos.y << "\n";
//
//	if (towerTowerExisted(worldPos)) {
//		return;//If the tower exist do sth(sell, upgrate)
//
//	}
//
//	else {//There is no tower in this Build Zone
//		if (isBuildMenuOpen) {
//			// TÍNH TOÁN BOUNDS NGAY TẠI ĐÂY
//			if (buildMenuTower1Icon->getGlobalBounds().contains(worldPos)) {
//				if (money >= TOWER1_COST) {
//					money -= TOWER1_COST;
//					buildTower(theTowerPosition, "Tower1");
//
//				}
//				closeBuildMenu();
//			}
//			else if (buildMenuTower2Icon->getGlobalBounds().contains(worldPos)) {
//				if (money >= TOWER2_COST) {
//					money -= TOWER2_COST;
//					buildTower(theTowerPosition, "Tower2");
//				}
//
//				closeBuildMenu();
//			}
//			else if (buildMenuTower3Icon->getGlobalBounds().contains(worldPos)) {
//				if (money >= TOWER3_COST) {
//					money -= TOWER3_COST;
//					buildTower(theTowerPosition, "Tower3");
//				}
//
//				closeBuildMenu();
//			}
//			else if (buildMenuTower4Icon->getGlobalBounds().contains(worldPos)) {
//				if (money >= TOWER4_COST) {
//					money -= TOWER4_COST;
//					buildTower(theTowerPosition, "Tower4");
//
//				}
//
//				closeBuildMenu();
//			}
//			else {
//				closeBuildMenu();
//			}
//		}
//		else {
//			int row = static_cast<int>(worldPos.y / point::TileSize);
//			int col = static_cast<int>(worldPos.x / point::TileSize);
//			if (clickCheck(worldPos)) {//Check to see if there is a BuildZone here (Tile that can build tower)
//				openBuildMenu(row, col);
//				theTowerPosition = worldPos;//Save the Placing Position for Tower
//			}
//		}
//	}
//
//}
//
//bool TowerManager::clickCheck(sf::Vector2f worldPos) {
//	for (int i = 0; i < buildZones.size(); ++i) {//Check all the Building Tile avaiable
//		if (buildZones[i].bounds.contains(worldPos)) {
//			return true;//If there are return true
//		}
//	}
//	return false;//No Building tile here
//}
//
//
//void TowerManager::sellTower() {
//
//}
//
//void TowerManager::upgrateTower()
//{
//}
//
//void TowerManager::draw(sf::RenderWindow& window) {
//	for (int i = 0; i < towers.size(); ++i) {
//		towers[i]->draw(window);
//	}
//
//	if (isBuildMenuOpen) {
//		if (buildMenuBackground) window.draw(*buildMenuBackground);
//		if (buildMenuTower1Icon) window.draw(*buildMenuTower1Icon);
//		if (buildMenuTower2Icon) window.draw(*buildMenuTower2Icon);
//		if (buildMenuTower3Icon) window.draw(*buildMenuTower3Icon);
//		if (buildMenuTower4Icon) window.draw(*buildMenuTower4Icon);
//
//
//		for (const auto& s : tower1CostSprites) window.draw(s);
//		for (const auto& s : tower2CostSprites) window.draw(s);
//		for (const auto& s : tower3CostSprites) window.draw(s);
//		for (const auto& s : tower4CostSprites) window.draw(s);
//
//
//	}
//
//	//for (const auto& zone : buildZones) {
//	//sf::RectangleShape shape;
//	//shape.setPosition(sf::Vector2f(zone.bounds.position));
//	//shape.setSize(sf::Vector2f(zone.bounds.size));
//	//shape.setFillColor(sf::Color::Transparent);
//	//shape.setOutlineColor(sf::Color::Green);
//	//shape.setOutlineThickness(1.f);
//	//window.draw(shape);
//	//}
//
//}
//
//


#include "TowerManager.h"
#include <fstream>
#include <algorithm> // Cần cho std::find

// --- CONSTRUCTOR & DESTRUCTOR ---
TowerManager::TowerManager(sf::RenderWindow* window, BulletManager* rbulletManager)
    : m_window(window), m_bulletManager(rbulletManager),
    m_isBuildMenuOpen(false), m_isUpgradeMenuOpen(false), m_selectedTower(nullptr)
{
    setupMenus();
}

TowerManager::~TowerManager() {
    for (auto* t : m_towers) {
        delete t;
    }
}

// --- SETUP & QUẢN LÝ MENUS ---
void TowerManager::setupMenus() {
    m_buildMenuBG = std::make_unique<sf::RectangleShape>();
    m_buildMenuBG->setSize({ 148.f, 60.f });
    m_buildMenuBG->setFillColor(sf::Color(100, 100, 100, 220));
    m_buildIcon1 = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower1_Icon")[0]);
    m_buildIcon2 = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower2_Icon")[0]);
    m_buildIcon3 = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower3_Icon")[0]);
    m_buildIcon4 = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower4_Icon")[0]);

    m_upgradeMenuBG = std::make_unique<sf::RectangleShape>();
    m_upgradeMenuBG->setSize({ 74.f, 60.f });
    m_upgradeMenuBG->setFillColor(sf::Color(120, 120, 120, 220));
    m_upgradeIcon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Upgrade_Icon")[0]);
    m_sellIcon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Sell_Icon")[0]);
}

void TowerManager::openBuildMenu(sf::Vector2f position) {
    closeUpgradeMenu();
    m_isBuildMenuOpen = true;
    m_buildPosition = position;

    sf::Vector2f menuSize = m_buildMenuBG->getSize();
    float menuX = position.x - (menuSize.x / 2.f);
    float menuY = position.y - (point::TileSize / 2.f) - menuSize.y - 5.f;

    // Đảm bảo menu không bị vẽ ra ngoài màn hình
    const sf::Vector2u windowSize = m_window->getSize();
    if (menuX < 0) menuX = 0;
    if (menuY < 0) menuY = 0;
    if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
    if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;

    m_buildMenuBG->setPosition({ menuX, menuY });
    m_buildIcon1->setPosition({ menuX + 5.f, menuY + 2.5f });
    m_buildIcon2->setPosition({ menuX + 42.f, menuY + 2.5f });
    m_buildIcon3->setPosition({ menuX + 79.f, menuY + 2.5f });
    m_buildIcon4->setPosition({ menuX + 116.f, menuY + 2.5f });
}

void TowerManager::closeBuildMenu() {
    m_isBuildMenuOpen = false;
}

void TowerManager::openUpgradeMenu(tower* targetTower) {
    closeBuildMenu();
    m_isUpgradeMenuOpen = true;
    m_selectedTower = targetTower;

    sf::Vector2f towerPos = m_selectedTower->getPosition();
    sf::Vector2f menuSize = m_upgradeMenuBG->getSize();
    float menuX = towerPos.x - (menuSize.x / 2.f);
	float menuY = towerPos.y - (point::TileSize / 2.f) - menuSize.y - 5.f; // 5.f là khoảng đệm

    // Đảm bảo menu không bị vẽ ra ngoài màn hình
    const sf::Vector2u windowSize = m_window->getSize();
    if (menuX < 0) menuX = 0;
    if (menuY < 0) menuY = 0;
    if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
    if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;

    m_upgradeMenuBG->setPosition({ menuX, menuY });
    m_upgradeIcon->setPosition({ menuX + 5.f, menuY + 2.5f });
    m_sellIcon->setPosition({ menuX + 42.f, menuY + 2.5f });
}

void TowerManager::closeUpgradeMenu() {
    m_isUpgradeMenuOpen = false;
    m_selectedTower = nullptr;
}

// --- LOGIC GAME CHÍNH ---
void TowerManager::ReadFile(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (fin.fail()) {
        throw std::runtime_error("Fail to open build_Position.txt");
    }
    m_buildZones.clear();
    float row, col;
    std::string ignoreline;
    getline(fin, ignoreline);
    while (fin >> row >> col) {
        sf::FloatRect zone(
            { col * point::TileSize, row * point::TileSize },
            { (float)point::TileSize, (float)point::TileSize }
        );
        m_buildZones.push_back({ zone, false });
    }
}

void TowerManager::handleMouseClick(sf::Vector2f worldPos, int& money) {
    std::cout << "gfqgqsdafcg";
    // 1. Ưu tiên xử lý click vào menu đang mở
    if (m_isUpgradeMenuOpen) {
        if (m_upgradeIcon->getGlobalBounds().contains(worldPos)) {
            if (m_selectedTower && money >= m_selectedTower->getUpgradeCost()) {
                money -= m_selectedTower->getUpgradeCost();
                m_selectedTower->upgrade();
            }
        }
        else if (m_sellIcon->getGlobalBounds().contains(worldPos)) {
            if (m_selectedTower) {
                money += m_selectedTower->getSellValue();
                for (auto& zone : m_buildZones) {
                    if (zone.bounds.contains(m_selectedTower->getPosition())) {
                        zone.towerExist = false;
                        break;
                    }
                }
                auto it = std::find(m_towers.begin(), m_towers.end(), m_selectedTower);
                if (it != m_towers.end()) {
                    delete* it;
                    m_towers.erase(it);
                }
            }
        }
        closeUpgradeMenu();
        return;
    }

    if (m_isBuildMenuOpen) {
        int row = static_cast<int>(m_buildPosition.y / point::TileSize);
        int col = static_cast<int>(m_buildPosition.x / point::TileSize);

        if (m_buildIcon1->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER1_COST) { money -= TOWER1_COST; buildTower(row, col, "Tower1"); }
        }
        else if (m_buildIcon2->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER2_COST) { money -= TOWER2_COST; buildTower(row, col, "Tower2"); }
        }
        else if (m_buildIcon3->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER3_COST) { money -= TOWER3_COST; buildTower(row, col, "Tower3"); }
        }
        else if (m_buildIcon4->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER4_COST) { money -= TOWER4_COST; buildTower(row, col, "Tower4"); }
        }
        closeBuildMenu();
        return;
    }

    // 2. Nếu không có menu nào mở, kiểm tra click trên map
    for (auto* t : m_towers) {
        if (t->getGlobalBounds().contains(worldPos)) {
            openUpgradeMenu(t);
            return;
        }
    }

    for (const auto& zone : m_buildZones) {
        if (!zone.towerExist && zone.bounds.contains(worldPos)) {
            openBuildMenu(zone.bounds.getCenter());
            return;
        }
    }
}

bool TowerManager::buildTower(int row, int col, const std::string& towerType) {
    tower* newTower = new tower(towerType, Resource_Management::getTexture(towerType), row, col);
    float centerX = static_cast<float>(col * point::TileSize) + (point::TileSize / 2.f);
    float centerY = static_cast<float>(row * point::TileSize) + (point::TileSize / 2.f);
    newTower->setPosition({ centerX, centerY });
    m_towers.emplace_back(newTower);

    for (auto& zone : m_buildZones) {
        if (zone.bounds.contains({ centerX, centerY })) {
            zone.towerExist = true;
            return true;
        }
    }
    return false; // Không nên xảy ra nếu logic đúng
}

bool TowerManager::towerTowerExisted(int row, int col) {
    for (const auto& t : m_towers) {
        if (t->getRow() == row && t->getCol() == col) return true;
    }
    return false;
}

void TowerManager::update(float deltaTime, std::vector<enemy*>& enemies) {
    for (auto* t : m_towers) {
        t->update(deltaTime, enemies, m_bulletManager);
    }
}

// --- CÁC HÀM VẼ ---
//void TowerManager::draw(sf::RenderWindow& window) {
//    for (auto* t : m_towers) {
//        t->draw(window);
//    }
//
//    if (m_isBuildMenuOpen) {
//        window.draw(*m_buildMenuBG);
//        window.draw(*m_buildIcon1);
//        window.draw(*m_buildIcon2);
//        window.draw(*m_buildIcon3);
//        window.draw(*m_buildIcon4);
//
//        drawNumber(TOWER1_COST, m_buildIcon1->getPosition().x, m_buildIcon1->getPosition().y + 32);
//        drawNumber(TOWER2_COST, m_buildIcon2->getPosition().x, m_buildIcon2->getPosition().y + 32);
//        drawNumber(TOWER3_COST, m_buildIcon3->getPosition().x, m_buildIcon3->getPosition().y + 32);
//        drawNumber(TOWER4_COST, m_buildIcon4->getPosition().x, m_buildIcon4->getPosition().y + 32);
//    }
//
//    if (m_isUpgradeMenuOpen) {
//        window.draw(*m_upgradeMenuBG);
//        window.draw(*m_upgradeIcon);
//        window.draw(*m_sellIcon);
//
//        if (m_selectedTower) {
//            drawNumber(m_selectedTower->getUpgradeCost(), m_upgradeIcon->getPosition().x, m_upgradeIcon->getPosition().y + 32);
//            drawNumber(m_selectedTower->getSellValue(), m_sellIcon->getPosition().x, m_sellIcon->getPosition().y + 32);
//        }
//    }
//}

void TowerManager::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
	sprite_vector.clear(); // Xóa các sprite cũ
    std::string numStr = std::to_string(number);
    float currentX = x;
    const float digitScale = 0.6f;
    m_costSprites.clear();
    for (char c : numStr) {
        int digit = c - '0';
        sf::Sprite sprite(Resource_Management::Digits[digit][0]);
        sprite.setScale(sf::Vector2f(digitScale, digitScale));
        sprite.setPosition({ currentX, y });
        sprite_vector.push_back(sprite); // Thêm sprite vào vector
        currentX += sprite.getGlobalBounds().size.x;
    }
  
}

// TowerManager.cpp -> draw
void TowerManager::draw(sf::RenderWindow& window) { // << Nhận vào window
    for (auto* t : m_towers) {
        t->draw(window);
    }

    if (m_isBuildMenuOpen) {
        // ... vẽ menu xây dựng ...
        drawNumber(TOWER1_COST, m_buildIcon1->getPosition().x, m_buildIcon1->getPosition().y + 32, m_costSprites);
        for (const auto& s : m_costSprites) window.draw(s); // Vẽ các sprite đã được chuẩn bị
        // ... làm tương tự cho các giá tiền khác
    }

    if (m_isUpgradeMenuOpen) {
        // ... vẽ menu nâng cấp ...
        if (m_selectedTower) {
            drawNumber(m_selectedTower->getUpgradeCost(), m_upgradeIcon->getPosition().x, m_upgradeIcon->getPosition().y + 32, m_costSprites);
            for (const auto& s : m_costSprites) window.draw(s);
            drawNumber(m_selectedTower->getSellValue(), m_sellIcon->getPosition().x, m_sellIcon->getPosition().y + 32, m_costSprites);
            for (const auto& s : m_costSprites) window.draw(s);
        }
    }
}

void TowerManager::reset() {
    for (auto* t : m_towers) {
        delete t;
    }
    m_towers.clear();

    for (auto& zone : m_buildZones) {
        zone.towerExist = false;
    }
    closeBuildMenu();
    closeUpgradeMenu();
}