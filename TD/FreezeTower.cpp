#include "FreezeTower.h"
#include "BulletManager.h"//Tạo đạn
#include "enemy.h"	//để chỉ enemy
#include "TowerManager.h" // Cần để lấy TOWER_COST

FreezeTower::FreezeTower(std::string towerType)
    : tower(towerType)
{
    towerTexture = &Resource_Management::FreezeTower;
    towerSprite.setTexture((*towerTexture)[0]);

    totalFrame = (*towerTexture).size();
    float scale = 0.07f;
    towerSprite.setScale({ scale, scale });

    if (!(*towerTexture).empty()) {
        towerSprite.setOrigin({ towerSprite.getLocalBounds().size.x / 3.2f, towerSprite.getLocalBounds().size.y / 1.75f });
    }

    damage = 15; range = 170.f; fireRate = 1.2f; upgradeCost = 100; sellValue = TOWER2_COST / 2;
}

void FreezeTower::update(float dt, std::vector<enemy*>& enemies, BulletManager* bulletManager) {
    animate(dt);
    reloadTime -= dt; 
    if (reloadTime > 0.f) return;
    enemy* target = findTheNearestEnemyInRange(enemies);
    if (target) {
        // spawn normal bullet; to implement slow effect, extend bullet/enemy
        bulletManager->spawBullet(this, target, damage, "IceBullet");
        reloadTime = fireRate;
    }
}

void FreezeTower::upgrade() {
    tower::upgrade();
    sf::FloatRect bounds = this->towerSprite.getLocalBounds();
    this->towerSprite.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 1.5f)); // Căn tâm
}