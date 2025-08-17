#include "FlameTower.h"
#include "MathHelpers.h"
#include <algorithm>
#include <utility>
#include "BulletManager.h"//Tạo đạn
#include "enemy.h"	//để chỉ enemy
#include "TowerManager.h" // Cần để lấy TOWER_COST

// SplashTower constructor: moderate damage and range, fires at multiple enemies
FlameTower::FlameTower(std::string towerType)
    : tower(towerType) {
    towerTexture = &Resource_Management::FlameTower;
    towerSprite.setTexture((*towerTexture)[0]);

    totalFrame = (*towerTexture).size();
    float scale = 0.07f;
    towerSprite.setScale({ scale, scale });

    if (!(*towerTexture).empty()) {
        towerSprite.setOrigin({ towerSprite.getLocalBounds().size.x / 2.25f, towerSprite.getLocalBounds().size.y / 1.3f });
    }

    damage = 60; range = 120.f; fireRate = 2.0f; upgradeCost = 200; sellValue = TOWER4_COST / 2;
}

void FlameTower::update(float dt, std::vector<enemy*>& enemies,
    BulletManager* bulletManager) {
    animate(dt);
    reloadTime -= dt;
    if (reloadTime > 0.f)
        return;
    // Build list of enemies within range and sort by distance
    std::vector<std::pair<enemy*, float>> inRange;
    sf::Vector2f pos = towerSprite.getPosition();
    for (auto* e : enemies) {
        if (!e || !e->isEnemyAlive()) continue;
        float dist = MathHelpers::Distance(pos, e->getPosition());
        if (dist <= range) {
            inRange.emplace_back(e, dist);
        }
    }
    if (inRange.empty()) return;
    std::sort(inRange.begin(), inRange.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    // Fire at up to three closest enemies
    size_t shots = std::min<size_t>(3, inRange.size());
    for (size_t i = 0; i < shots; ++i) {
        bulletManager->spawBullet(this, inRange[i].first, damage, "FlameBullet");
    }
    reloadTime = fireRate;
}

void FlameTower::upgrade() {
    tower::upgrade();
}