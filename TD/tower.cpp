#include "tower.h"
#include "BulletManager.h"//Tạo đạn
#include "enemy.h"	//để chỉ enemy
#include "TowerManager.h" // Cần để lấy TOWER_COST

tower::tower(const std::string& type)
// --- XÓA towerSprite() RA KHỎI ĐÂY ---
	: towerTexture(&Resource_Management::FlameTower),
	towerSprite((*towerTexture)[0]),
	towerType(type),
	level(1),
	reloadTime(0.0f),
	currentFrame(0), frameTime(0.2f), timeSinceLastFrame(0.0f)
{
	if (!(*towerTexture).empty()) {
		towerSprite.setOrigin(towerSprite.getLocalBounds().size / 2.f);
	}
}

void tower::upgrade() {
	level++;
	range *= 1.1f;
	damage = static_cast<int>(damage * 1.25f);
	fireRate *= 0.9f;
	sellValue += upgradeCost / 2;
	upgradeCost = static_cast<int>(upgradeCost * 1.5f);
	std::string nextLevelTextureName = towerType + "_L" + std::to_string(level); // Tạo tên, ví dụ: "Tower1_L2"

	try {
		const std::vector<sf::Texture>& newTextures = Resource_Management::getTexture(nextLevelTextureName);
		if (!newTextures.empty()) {
			this->towerTexture = &newTextures; // Cập nhật lại bộ texture của trụ
			this->towerSprite.setTexture((*this->towerTexture)[0], true); // Gán texture mới, true để reset texture rect
			float scale_L2 = 1.0f; // Tỷ lệ mặc định
			if (towerType == "DarkTower") {
				scale_L2 = 0.08f; // Scale mới cho Tower1 cấp 2
			}
			else if (towerType == "FreezeTower") {
				scale_L2 = 0.07f; // Scale mới cho Tower2 cấp 2
			}
			else if (towerType == "ElectricTower") {
				scale_L2 = 0.08f;
			}
			else if (towerType == "FlameTower") {
				scale_L2 = 0.08f;
			}
			this->towerSprite.setScale({ scale_L2, scale_L2 });
			// Rất quan trọng: Căn lại origin vì kích thước ảnh mới có thể khác
			//sf::FloatRect bounds = this->towerSprite.getLocalBounds();
			//this->towerSprite.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y)); // Căn đáy-giữa
	
			
			// Reset animation
			this->currentFrame = 0;
			this->totalFrame = (*this->towerTexture).size();
		}
	}
	catch (const std::runtime_error& e) {
		// Xử lý trường hợp không tìm thấy texture cấp 2
		std::cerr << "Could not find upgrade texture: " << e.what() << std::endl;
		level--; // Hoàn lại level nếu load thất bại
	}
}

void tower::updadeToLevel(int toLevel) {//Upgrade to a specific level
	while (level < toLevel) {
		upgrade();
	}
}

void tower::update(float deltaTime, std::vector<enemy*>& enemies, BulletManager* bulletManager) {
	animate(deltaTime);
	reloadTime -= deltaTime;
	enemy* target = findTheNearestEnemyInRange(enemies);

	if (target && reloadTime <= 0.0f) {
		bulletManager->spawBullet(this, target, this->damage, "IceBullet");
		reloadTime = fireRate;
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
		towerSprite.setTexture((*towerTexture)[currentFrame]);
		timeSinceLastFrame = 0.0F;
	}
}