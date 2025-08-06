#include "tower.h"
#include "BulletManager.h"
#include "enemy.h"



tower::tower(const std::string& type, const std::vector<sf::Texture>& rtowerTexture, int row, int col)
	: towerTexture(rtowerTexture),
	towerSprite(rtowerTexture[0]),
	row(row), col(col),
	towerType(type),
	level(1),
	towerReloading(0.0f),
	currentFrame(0),
	frameTime(0.2f), // Giảm thời gian để animation nhanh hơn
	timeSinceLastFrame(0.0f)
{
	totalFrame = towerTexture.size();
	towerSprite.setOrigin(towerSprite.getLocalBounds().size / 2.f);

	// Gán chỉ số ban đầu dựa trên loại trụ (bạn có thể chỉnh lại các con số này)
	if (type == "Tower1") {
		damage = 25; range = 150.f; FireRate = 1.0f; upgradeCost = 75; sellValue = 50;
	}
	else if (type == "Tower2") {
		damage = 15; range = 170.f; FireRate = 1.2f; upgradeCost = 100; sellValue = 75;
	}
	else if (type == "Tower3") {
		damage = 40; range = 140.f; FireRate = 1.5f; upgradeCost = 150; sellValue = 100;
	}
	else if (type == "Tower4") {
		damage = 60; range = 120.f; FireRate = 2.0f; upgradeCost = 200; sellValue = 125;
	}
}


void tower::upgrade() {
	level++;
	// Tăng chỉ số (ví dụ)
	range *= 1.1f;
	damage = static_cast<int>(damage * 1.2f);
	FireRate *= 0.9f; // Bắn nhanh hơn

	// Cập nhật giá trị mới
	sellValue += upgradeCost / 2;
	upgradeCost = static_cast<int>(upgradeCost * 1.5f);
}




void tower::update(const float& deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager) {
	animate(deltaTime);
	towerReloading -= deltaTime;

	enemy* target = findTheNearestEnemyInRange(enemies);

	if (target && towerReloading <= 0.00f) {
		bulletManager->spawBullet(this, target, this->damage);

		towerReloading = FireRate;

	}
}

sf::FloatRect tower::getGlobalBounds() const {
	return towerSprite.getGlobalBounds();
}

enemy* tower::findTheNearestEnemyInRange(std::vector<enemy*>& enemies) {
	if (enemies.empty()) return nullptr;
	enemy* Target = nullptr;

	float minDistance = 999999;
	sf::Vector2f towerPosition = this->getPosition();

	for (int i = 0; i < enemies.size(); ++i) {
		float distance = MathHelpers::Distance(towerPosition, enemies[i]->getPosition());

		if (distance < range) {

			if (distance < minDistance) {
				minDistance = distance;
				Target = enemies[i];
			}
		}
	}
	return Target;
}

void tower::draw(sf::RenderWindow& window)
{
	window.draw(towerSprite);
}

//void tower::setMap_GameForBullet(point a[][point::Map_Game_SIZE]) {//Update mapTowerDefense_Game dữa trên cái mapTowerDefense_Game mình tạo ra
//	for (int i = 0; i < point::Map_Game_SIZE; i++) {
//		for (int j = 0; j < point::Map_Game_SIZE; j++) {
//			_b.UpdateMap_Game(i, j, a[i][j]);//Cập nhật đường đi cho viên đạn
//		}
//	}
//}

void tower::animate(float deltaTime) {
	timeSinceLastFrame += deltaTime; //Thoi gian giua cac Frame
	if (timeSinceLastFrame >= frameTime) { //Neu du thoi gian chuyen frame
		currentFrame = (currentFrame + 1) % totalFrame;

		towerSprite.setTexture(towerTexture[currentFrame]);//Dat frame ke tiep
		timeSinceLastFrame = 0.0F;
	}
}

void tower::setPosition(sf::Vector2f position) {
	towerSprite.setPosition(position);
}

sf::Vector2f tower::getPosition() const {
	return towerSprite.getPosition();
}