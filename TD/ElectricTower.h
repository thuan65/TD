#pragma once
#include "tower.h"
#include "Resource_Management.h"
#include <string>

class enemy;
class BulletManager;

// RapidTower – fires quickly with low damage.  Derived from Tower.
class ElectricTower : public tower {
public:
    ElectricTower(std::string towerType);
    void update(float dt, std::vector<enemy*>& enemies,
        BulletManager* bulletManager) override;
    void upgrade() override;
};