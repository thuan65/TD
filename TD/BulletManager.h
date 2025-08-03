#pragma once
#include "point.h"
#include "bullet.h"
#include "tower.h"
#include "enemy.h"
#include "Resource_Management.h"
#include <vector>

class BulletManager {
public:
	BulletManager();
	~BulletManager();

	void spawBullet(tower* theTower, enemy* enemies);
	void update(float deltatime, const std::vector<enemy*>& activeEnemies); // Sửa ở đây
	void processRemovals();
	void draw(sf::RenderWindow& window);

private:
	std::vector<bullet*> bullets;
	std::vector<bullet*> _bulletToRemove;
};