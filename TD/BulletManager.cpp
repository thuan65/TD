#include "BulletManager.h"
#include <algorithm> // Thêm thư viện

BulletManager::BulletManager() {}

void BulletManager::spawBullet(tower* theTower, enemy* enemies) {
	bullets.emplace_back(new bullet(Resource_Management::getTexture("bullet")));
	bullets.back()->Initialize(theTower, enemies);
}

// Sửa lại hoàn toàn hàm update
void BulletManager::update(float deltaTime, const std::vector<enemy*>& activeEnemies) {
	for (int i = 0; i < bullets.size(); ++i) {
		bullets[i]->Update(deltaTime);

		if (bullets[i]->getTimeBeforeCollide() <= 0.0f) {
			enemy* target = bullets[i]->getTarget();

			auto it = std::find(activeEnemies.begin(), activeEnemies.end(), target);

			if (it != activeEnemies.end()) {
				target->damageTake(bullets[i]->getDamage());
			}

			_bulletToRemove.push_back(bullets[i]);
		}
	}
	processRemovals();
}

void BulletManager::processRemovals() {
	if (!_bulletToRemove.empty()) {
		while (!_bulletToRemove.empty()) {
			bullet* target = _bulletToRemove.back();
			int tmp = -1;
			for (int i = 0; i < bullets.size(); ++i) {
				if (target == bullets[i]) {
					tmp = i;
					break;
				}
			}
			if (tmp == -1) continue;
			delete bullets[tmp];
			bullets.erase(bullets.begin() + tmp);
			_bulletToRemove.pop_back();
		}
	}
}

void BulletManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < bullets.size(); ++i) {
		bullets[i]->draw(window);
	}
}

BulletManager::~BulletManager() {
	for (int i = 0; i < bullets.size(); ++i) {
		delete bullets[i];
		bullets[i] = nullptr;
	}
	bullets.clear();
}