#include "tower.h"
#include "BulletManager.h"

tower::tower(const std::vector<sf::Texture>& rtowerTexture, int row, int col, float rRange, float rFireRate)
	: towerTexture(rtowerTexture), towerSprite(towerTexture[0]), range(rRange), FireRate(rFireRate), towerReloading(FireRate), totalFrame(towerTexture.size())
{
	//towerSprite.setPosition(sf::Vector2f(col * point::TileSize, row * point::TileSize));
	towerSprite.setOrigin(sf::Vector2f{ towerSprite.getLocalBounds().size / 2.f });//Canh giữa cho ảnh tháp
}

void tower::update(const float& deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager) {
	animate(deltaTime);
	towerReloading -= deltaTime;

	enemy* target = findTheNearestEnemyInRange(enemies);

	if (target && towerReloading <= 0.00f) {
		bulletManager->spawBullet(this, target);

		towerReloading = FireRate;

	}
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