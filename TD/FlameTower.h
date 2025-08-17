#pragma once
#include "tower.h"
#include "Resource_Management.h"
#include <string>

class enemy;
class BulletManager;

// SplashTower – fires a volley of bullets hitting multiple enemies.
class FlameTower : public tower {
public:
    FlameTower(std::string towerType);
    void update(float dt, std::vector<enemy*>& enemies,
        BulletManager* bulletManager) override;
    void upgrade() override;
};