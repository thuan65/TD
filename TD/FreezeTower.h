#pragma once
#include "tower.h"
#include "Resource_Management.h"
#include <string>

class enemy;
class BulletManager;

// FreezeTower – fires projectiles that could slow enemies (effect to be implemented)
class FreezeTower : public tower {
public:
    FreezeTower(std::string towerType);
    void update(float dt, std::vector<enemy*>& enemies, BulletManager* bulletManager) override;
    void upgrade() override;
};