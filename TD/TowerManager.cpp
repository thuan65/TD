#include "TowerManager.h"
#include "tower.h"
#include <algorithm> // Cần cho std::find

// --- CONSTRUCTOR & DESTRUCTOR ---
TowerManager::TowerManager(sf::RenderWindow* window, BulletManager* rbulletManager, WaveManager*)
    : window(window), bulletManager(rbulletManager), waveControl(waveControl),
    isBuildMenuOpen(false), isUpgradeMenuOpen(false), selectedTower(nullptr)
{
    setupBuildMenu();
}

TowerManager::~TowerManager() {
    for (auto* t : towers) {
        delete t;
    }
}

// --- SETUP & QUẢN LÝ MENUS ---
void TowerManager::setupBuildMenu() {
    buildMenuBackground = std::make_unique<sf::RectangleShape>();
    buildMenuBackground->setSize({ 148.f, 60.f });
    buildMenuBackground->setFillColor(sf::Color(100, 100, 100, 220));

    buildMenuTower1Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower1_Icon")[0]);
    buildMenuTower2Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower2_Icon")[0]);
    buildMenuTower3Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower3_Icon")[0]);
    buildMenuTower4Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower4_Icon")[0]);

    upgradeMenuBackground = std::make_unique<sf::RectangleShape>();
    upgradeMenuBackground->setSize({ 74.f, 60.f });
    upgradeMenuBackground->setFillColor(sf::Color(120, 120, 120, 220));
    upgradeButtonIcon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Upgrade_Icon")[0]);
    sellButtonIcon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Sell_Icon")[0]);

    const float iconScaleUpdate = 0.05f; // Ví dụ: thu nhỏ còn 80%. Bạn có thể thay đổi số này.
    const float iconScaleSell = 0.03f;
   

    // With this corrected line:  
    upgradeButtonIcon->setScale(sf::Vector2f(iconScaleUpdate, iconScaleUpdate));
    sellButtonIcon->setScale(sf::Vector2f(iconScaleSell, iconScaleSell));
}

void TowerManager::openBuildMenu(int row, int col) {
    closeUpgradeMenu();
    isBuildMenuOpen = true;

    float tileCenterX = static_cast<float>(col * point::TileSize) + (point::TileSize / 2.f);
    float tileCenterY = static_cast<float>(row * point::TileSize) + (point::TileSize / 2.f);
    theTowerPosition = { tileCenterX, tileCenterY };

    sf::Vector2f menuSize = buildMenuBackground->getSize();
    float menuX = theTowerPosition.x - (menuSize.x / 2.f);
    float menuY = theTowerPosition.y - (point::TileSize / 2.f) - menuSize.y - 5.f;

    // Đảm bảo menu không bị vẽ ra ngoài màn hình
    const sf::Vector2u windowSize = window->getSize();
    if (menuX < 0) menuX = 0;
    if (menuY < 0) menuY = 0;
    if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
    if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;

    buildMenuBackground->setPosition({ menuX, menuY });
    buildMenuTower1Icon->setPosition({ menuX + 5.f, menuY + 2.5f });
    buildMenuTower2Icon->setPosition({ menuX + 42.f, menuY + 2.5f });
    buildMenuTower3Icon->setPosition({ menuX + 79.f, menuY + 2.5f });
    buildMenuTower4Icon->setPosition({ menuX + 116.f, menuY + 2.5f });

    drawNumber(TOWER1_COST, buildMenuTower1Icon->getPosition().x, buildMenuTower1Icon->getPosition().y + 50, tower1CostSprites);
    drawNumber(TOWER2_COST, buildMenuTower2Icon->getPosition().x, buildMenuTower2Icon->getPosition().y + 50, tower2CostSprites);
    drawNumber(TOWER3_COST, buildMenuTower3Icon->getPosition().x, buildMenuTower3Icon->getPosition().y + 50, tower3CostSprites);
    drawNumber(TOWER4_COST, buildMenuTower4Icon->getPosition().x, buildMenuTower4Icon->getPosition().y + 50, tower4CostSprites);
}

void TowerManager::closeBuildMenu() {
    isBuildMenuOpen = false;
}

void TowerManager::openUpgradeMenu(tower* targetTower) {
    closeBuildMenu();
    isUpgradeMenuOpen = true;
    selectedTower = targetTower;

    sf::Vector2f towerPos = selectedTower->getPosition();
    sf::Vector2f menuSize = upgradeMenuBackground->getSize();
    float menuX = towerPos.x - (menuSize.x / 2.f);
    float menuY = towerPos.y - (selectedTower->getGlobalBounds().size.y / 2.f) - menuSize.y - 5.f;

    // Đảm bảo menu không bị vẽ ra ngoài màn hình
    const sf::Vector2u windowSize = window->getSize();
    if (menuX < 0) menuX = 0;
    if (menuY < 0) menuY = 0;
    if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
    if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;

    upgradeMenuBackground->setPosition({ menuX, menuY });
    upgradeButtonIcon->setPosition({ menuX + 5.f, menuY + 2.5f });
    sellButtonIcon->setPosition({ menuX + 42.f, menuY + 2.5f });
}

void TowerManager::closeUpgradeMenu() {
    isUpgradeMenuOpen = false;
    selectedTower = nullptr;
}

void TowerManager::setWaveManager(WaveManager* manager) {
    waveControl = manager;
}

// --- LOGIC GAME CHÍNH ---
//void TowerManager::ReadFile(const std::string& filePath) {
//    std::ifstream fin(filePath);
//    if (fin.fail()) {
//        throw std::runtime_error("Fail to open build_Position.txt for TowerManager");
//    }
//    buildZones.clear();
//    float row, col;
//    std::string ignoreline;
//    getline(fin, ignoreline);
//    while (fin >> row >> col) {
//        sf::FloatRect zone(
//            { col * point::TileSize, row * point::TileSize },
//            { (float)point::TileSize, (float)point::TileSize }
//        );
//        buildZones.push_back({ zone, false });
//    }
//}

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

void TowerManager::resolveTowerAt(sf::Vector2f worldPos, int& money) {
    if (isUpgradeMenuOpen) {
        if (upgradeButtonIcon->getGlobalBounds().contains(worldPos)) {
            if (selectedTower && money >= selectedTower->getUpgradeCost()) {
                money -= selectedTower->getUpgradeCost();
                selectedTower->upgrade();
            }
        }
        else if (sellButtonIcon->getGlobalBounds().contains(worldPos)) {
            if (selectedTower) {
                money += selectedTower->getSellValue();
                for (auto& zone : buildZones) {
                    if (zone.bounds.contains(selectedTower->getPosition())) {
                        zone.TowerExist = false;
                        break;
                    }
                }
                auto it = std::find(towers.begin(), towers.end(), selectedTower);
                if (it != towers.end()) {
                    delete* it;
                    towers.erase(it);
                }
            }
        }
        closeUpgradeMenu();
        return;
    }

    if (isBuildMenuOpen) {
     
        if (buildMenuTower1Icon->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER1_COST) { money -= TOWER1_COST; buildTower(theTowerPosition, "Tower1"); }
        }
        else if (buildMenuTower2Icon->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER2_COST) { money -= TOWER2_COST; buildTower(theTowerPosition, "Tower2"); }
        }
        else if (buildMenuTower3Icon->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER3_COST) { money -= TOWER3_COST; buildTower(theTowerPosition, "Tower3"); }
        }
        else if (buildMenuTower4Icon->getGlobalBounds().contains(worldPos)) {
            if (money >= TOWER4_COST) { money -= TOWER4_COST; buildTower(theTowerPosition, "Tower4"); }
        }
        closeBuildMenu();
        return;
    }

    // Nếu không có menu nào mở
    for (auto* t : towers) {
        if (t->getGlobalBounds().contains(worldPos)) {
            openUpgradeMenu(t);
            return;
        }
    }

    if (clickCheck(worldPos) && !towerTowerExisted(worldPos)) {
        int row = static_cast<int>(worldPos.y / point::TileSize);
        int col = static_cast<int>(worldPos.x / point::TileSize);
        openBuildMenu(row, col);
    }
}

//bool TowerManager::buildTower(sf::Vector2f worldPos, std::string towerType) {
//    int row = static_cast<int>(worldPos.y / point::TileSize);
//    int col = static_cast<int>(worldPos.x / point::TileSize);
//
//    tower* newTower = new tower(towerType, Resource_Management::getTexture(towerType), row, col);
//    newTower->setPosition(worldPos);
//    towers.emplace_back(newTower);
//
//    for (auto& zone : buildZones) {
//        if (zone.bounds.contains(worldPos)) {
//            zone.TowerExist = true;
//            return true;
//        }
//    }
//    return false;
//}

bool TowerManager::buildTower(sf::Vector2f worldPos, std::string towerType) {
    /*tower* buildNewTower = new tower(towerType, Resource_Management::getTexture(towerType));*/
    tower* buildNewTower = new tower(towerType, Resource_Management::getTexture(towerType), buildMenuTilePosition.y, buildMenuTilePosition.x);
    for (int i = 0; i < buildZones.size(); ++i) {//Tìm ô có thể xây tháp

        if (buildZones[i].bounds.contains(worldPos)) {
            sf::Vector2f towerPosition = buildZones[i].bounds.getCenter();
            towerPosition.y -= 12.5f;
            buildNewTower->setPosition(towerPosition);//Set the tower position in the middle of the Tile
            buildZones[i].TowerExist = true;
            //std::cout << "Build:  " << buildZones[i].bounds.getCenter().x << " " << buildZones[i].bounds.getCenter().y << "\n";
            //std::cout << buildNewTower->getPosition().x << " " << buildNewTower->getPosition().y << "\n";
            towers.emplace_back(buildNewTower);
            return true;
            break;
        }
    }
}

bool TowerManager::towerTowerExisted(sf::Vector2f worldPos) {
    for (const auto& zone : buildZones) {
        if (zone.bounds.contains(worldPos) && zone.TowerExist) {
            return true;
        }
    }
    return false;
}

bool TowerManager::towerTowerExisted(const buildZone& zone) {
    return zone.TowerExist;
}

bool TowerManager::clickCheck(sf::Vector2f worldPos) {
    for (const auto& zone : buildZones) {
        if (zone.bounds.contains(worldPos)) {
            return true;
        }
    }
    return false;
}

void TowerManager::update(float deltaTime) {
    std::vector<enemy*>& enemies = waveControl->getActiveEnemy();
    for (auto* t : towers) {
    
        t->update(deltaTime, enemies, bulletManager);
    }
}

// --- CÁC HÀM VẼ ---
void TowerManager::draw(sf::RenderWindow& window) {
    for (auto* t : towers) {
        t->draw(window);
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

    if (isBuildMenuOpen) {
        window.draw(*buildMenuBackground);
        window.draw(*buildMenuTower1Icon);
        window.draw(*buildMenuTower2Icon);
        window.draw(*buildMenuTower3Icon);
        window.draw(*buildMenuTower4Icon);

        for (const auto& s : tower1CostSprites) window.draw(s);
        for (const auto& s : tower2CostSprites) window.draw(s);
        for (const auto& s : tower3CostSprites) window.draw(s);
        for (const auto& s : tower4CostSprites) window.draw(s);
    }

    if (isUpgradeMenuOpen) {
        window.draw(*upgradeMenuBackground);
        window.draw(*upgradeButtonIcon);
        window.draw(*sellButtonIcon);

        if (selectedTower) {
            // Dùng costSprites chung để vẽ
            drawNumber(selectedTower->getUpgradeCost(), upgradeButtonIcon->getPosition().x, upgradeButtonIcon->getPosition().y + 32, costSprites);
            for (const auto& s : costSprites) window.draw(s);
            drawNumber(selectedTower->getSellValue(), sellButtonIcon->getPosition().x, sellButtonIcon->getPosition().y + 32, costSprites);
            for (const auto& s : costSprites) window.draw(s);
        }

    }
}

void TowerManager::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
    sprite_vector.clear();
    std::string numStr = std::to_string(number);
    float currentX = x;
    const float digitScale = 0.01f;
    for (char c : numStr) {
        int digit = c - '0';
        sf::Sprite sprite(Resource_Management::Digits[digit][0]);
        sprite.setScale(sf::Vector2f(digitScale, digitScale));
        sprite.setPosition({ currentX, y });
        sprite_vector.push_back(sprite);
        currentX += sprite.getGlobalBounds().size.x;
    }
}

void TowerManager::save(std::ostream& fileOut) const {
    fileOut << towers.size() << "\n"; //Số lượng tower đang có
    for (int i = 0; i < towers.size(); ++i) {
        fileOut << towers[i]->getTowerType() << " " << towers[i]->getTowerLevel() << " " << towers[i]->getPosition().x << " " << towers[i]->getPosition().y << "\n";
    }
}

void TowerManager::loadSave(std::istream& fileIn) {
    size_t towersSize;
    fileIn >> towersSize;//Số lượng tower đang có
    towers.reserve(towersSize);
    for (int i = 0; i < towersSize; ++i) {
        std::string TowerType;
        int TowerLevel;
        sf::Vector2f towerPosition;
        fileIn >> TowerType
            >> TowerLevel
            >> towerPosition.x >> towerPosition.y;

        addTower(TowerType, towerPosition, TowerLevel);
    }
}

void TowerManager::addTower(const string& towerType, sf::Vector2f towerPositon, int TowerLevel) {
    tower* buildNewTower = new tower(towerType, Resource_Management::getTexture(towerType));
    buildNewTower->setPosition(towerPositon);
    buildNewTower->updadeToLevel(TowerLevel);//Upgrate cho den level hien tai
    towers.emplace_back(buildNewTower);
}

// --- CÁC HÀM CHƯA DÙNG ĐẾN ---
void TowerManager::reset() {}
void TowerManager::sellTower() {}
void TowerManager::upgrateTower() {}