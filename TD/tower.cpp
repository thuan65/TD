#include "tower.h"
#include "BulletManager.h"
#include "enemy.h"
#include "TowerManager.h" // Cần để lấy TOWER_COST



tower::tower(const std::string& type, const std::vector<sf::Texture>& rtowerTexture, int row, int col)
// --- XÓA towerSprite() RA KHỎI ĐÂY ---
	: towerTexture(rtowerTexture),	
	towerSprite(towerTexture[0]),
	row(row), col(col),
	towerType(type),
	level(1),
	towerReloading(0.0f),
	currentFrame(0), frameTime(0.2f), timeSinceLastFrame(0.0f)
{
	// Tất cả logic xử lý sprite sẽ nằm trong thân hàm
	if (!towerTexture.empty()) {
		towerSprite.setTexture(towerTexture[0]);
		towerSprite.setOrigin(towerSprite.getLocalBounds().size / 2.f);
	}

	totalFrame = towerTexture.size();
	float scale = 1.0f; // Mặc định là 100%
	if (type == "Tower1") {
		scale = 1.0f; // Ví dụ: Thu nhỏ trụ 1 còn 80%
	}
	else if (type == "Tower2") {
		scale = 0.08f; // Ví dụ: Thu nhỏ trụ băng mới (48x48) còn 60%
	}
	towerSprite.setScale({ scale, scale });

	if (type == "Tower1") {
		damage = 25; range = 150.f; FireRate = 1.0f; upgradeCost = 75; sellValue = TOWER1_COST / 2;
	}
	else if (type == "Tower2") {
		damage = 15; range = 170.f; FireRate = 1.2f; upgradeCost = 100; sellValue = TOWER2_COST / 2;
	}
	else if (type == "Tower3") {
		damage = 40; range = 140.f; FireRate = 1.5f; upgradeCost = 150; sellValue = TOWER3_COST / 2;
	}
	else if (type == "Tower4") {
		damage = 60; range = 120.f; FireRate = 2.0f; upgradeCost = 200; sellValue = TOWER4_COST / 2;
	}
}

void tower::upgrade() {
	level++;
	range *= 1.1f;
	damage = static_cast<int>(damage * 1.25f);
	FireRate *= 0.9f;
	sellValue += upgradeCost / 2;
	upgradeCost = static_cast<int>(upgradeCost * 1.5f);
}

void tower::updadeToLevel(int toLevel) {//Upgrade to a specific level
	if (level < toLevel) {
		upgrade();
	}
}

void tower::update(float deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager) {
	animate(deltaTime);
	towerReloading -= deltaTime;
	enemy* target = findTheNearestEnemyInRange(enemies);

	if (target && towerReloading <= 0.0f) {
		bulletManager->spawBullet(this, target, this->damage);
		towerReloading = FireRate;
	}

}

void tower::draw(sf::RenderWindow& window) {
	window.draw(towerSprite);
}

void tower::setPosition(sf::Vector2f position) {
	towerSprite.setPosition(position);
}
sf::Vector2f tower::getPosition() const {
	return towerSprite.getPosition();
}
sf::FloatRect tower::getGlobalBounds() const {
	return towerSprite.getGlobalBounds();
}

enemy* tower::findTheNearestEnemyInRange(std::vector<enemy*>& enemies) {
	enemy* Target = nullptr;
	float minDistance = 999999;
	sf::Vector2f towerPosition = this->getPosition();

	for (enemy* currentEnemy : enemies) {
		if (currentEnemy && currentEnemy->isEnemyAlive()) {
			float distance = MathHelpers::Distance(towerPosition, currentEnemy->getPosition());
			if (distance <= range && distance < minDistance) {
				minDistance = distance;
				Target = currentEnemy;
				
			}
		}
	}

	return Target;
}

void tower::animate(float deltaTime) {
	if (totalFrame <= 1) return;
	timeSinceLastFrame += deltaTime;
	if (timeSinceLastFrame >= frameTime) {
		currentFrame = (currentFrame + 1) % totalFrame;
		towerSprite.setTexture(towerTexture[currentFrame]);
		timeSinceLastFrame = 0.0F;
	}
}