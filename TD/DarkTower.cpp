#include "DarkTower.h"
#include "BulletManager.h"//Tạo đạn
#include "enemy.h"	//để chỉ enemy
#include "TowerManager.h" // Cần để lấy TOWER_COST

// SniperTower constructor: set high damage and long range
DarkTower::DarkTower(std::string towerType)
    : tower(towerType) {
    towerTexture = &Resource_Management::DarkTower;
    towerSprite.setTexture((*towerTexture)[0]);

    totalFrame = (*towerTexture).size();
    float scale = 0.08f;
    towerSprite.setScale({ scale, scale });
    damage = 25; range = 150.f; fireRate = 1.0f; upgradeCost = 75; sellValue = TOWER1_COST / 2;
    if (!(*towerTexture).empty()) {
        towerSprite.setOrigin({ towerSprite.getLocalBounds().size.x / 2.0f, towerSprite.getLocalBounds().size.y / 1.25f });
    }
}

void DarkTower::update(float dt, std::vector<enemy*>& enemies,
    BulletManager* bulletManager) {
    animate(dt);
    reloadTime -= dt;
    enemy* target = findTheNearestEnemyInRange(enemies);
    if (target && reloadTime <= 0.f) {
        bulletManager->spawBullet(this, target, damage, "DarkBullet");
        reloadTime = fireRate;
    }
}

void DarkTower::upgrade() {
    tower::upgrade();
    sf::FloatRect bounds = this->towerSprite.getLocalBounds();
    this->towerSprite.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 1.25f)); // Căn tâm
}