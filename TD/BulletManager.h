#pragma once
#include "point.h"
#include "bullet.h"
#include "tower.h"
#include "enemy.h"
#include "Resource_Management.h"
#include <vector>

class WaveManager;

class BulletManager {
public:
	BulletManager(WaveManager* waveControl);
	~BulletManager();

	void spawBullet(tower* theTower, enemy* enemies, int damage);
	void update(float deltatime);
	void processRemovals();
	void draw(sf::RenderWindow& window);

private:
	WaveManager* waveControl;
	std::vector<bullet*> bullets;
	std::vector<bullet*> _bulletToRemove;
};