#include "ElectricTower.h"
#include "BulletManager.h"//Tạo đạn
#include "enemy.h"	//để chỉ enemy
#include "TowerManager.h" // Cần để lấy TOWER_COST

// RapidTower constructor: set sprite, range, damage, fire rate and costs
ElectricTower::ElectricTower(std::string towerType)
    : tower(towerType) {
        towerTexture = &Resource_Management::ElectricTower;
        towerSprite.setTexture((*towerTexture)[0]);

        totalFrame = (*towerTexture).size();
        float scale = 0.08f;
        towerSprite.setScale({ scale, scale });

        if (!(*towerTexture).empty()) {
            towerSprite.setOrigin({ towerSprite.getLocalBounds().size.x / 2.0f, towerSprite.getLocalBounds().size.y / 1.25f });
        }

        damage = 40; range = 140.f; fireRate = 1.5f; upgradeCost = 150; sellValue = TOWER3_COST / 2;
}

void ElectricTower::update(float dt, std::vector<enemy*>& enemies,
    BulletManager* bulletManager) {
    animate(dt);
    reloadTime -= dt;
    enemy* target = findTheNearestEnemyInRange(enemies);
    if (target && reloadTime <= 0.f) {
        bulletManager->spawBullet(this, target, damage, "LightningBullet");
        reloadTime = fireRate;
    }
}

void ElectricTower::upgrade() {
    tower::upgrade();
    sf::FloatRect bounds = this->towerSprite.getLocalBounds();
    this->towerSprite.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 1.25f)); // Căn tâm
}
