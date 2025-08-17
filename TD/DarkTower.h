#pragma once
#include "tower.h"
#include "Resource_Management.h"
#include <string>

class enemy;
class BulletManager;

// SniperTower – high damage, long range, slow firing tower.
class DarkTower : public tower {
public:
    DarkTower(std::string towerType);
    void update(float dt, std::vector<enemy*>& enemies,
        BulletManager* bulletManager) override;
    void upgrade() override;
};