#include "BulletManager.h"

BulletManager::BulletManager()
{
}

void BulletManager::spawBullet(tower* theTower,enemy* enemies) {
	bullets.emplace_back(new bullet(Resource_Management::getTexture("bullet")));
	bullets.back()->Initialize(theTower, enemies);
}

void BulletManager::update(float deltaTime) {
	for (int i = 0; i < bullets.size(); ++i) {
		bullets[i]->Update(deltaTime);

		//sf::Vector2f pos = bullets[i]->getPosition();
		//std::cout << pos.x << " " << pos.y << "\n";
		
		if (bullets[i]->getTimeBeforeCollide() <= 0.0f) {
			enemy* target = bullets[i]->getTarget();
			target->damageTake(bullets[i]->getDamage());
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
