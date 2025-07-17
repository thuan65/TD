#include "bullet.h"
#include "tower.h"
#include "enemy.h"

bullet::bullet(const std::vector<sf::Texture>& bulletTexure, int rSpeed, int rdamage)
	: bulletSprite(bulletTexure[0]), _speed(rSpeed), damage(rdamage)
{
	bulletSprite.setScale(sf::Vector2f(0.01, 0.01));
}

void bullet::Initialize(tower* theTower, enemy* theTarget) {
	if (theTower) {//if the tower is still exist
		target = theTarget;
		sf::Vector2f targetPosition = theTarget->getPosition();
		sf::Vector2f towerPostion = theTower->getPosition();

		

		sf::Vector2f deltaVectorFromTowerToTarget = targetPosition - towerPostion;
	
		//float distance = std::sqrt(deltaVectorFromTowerToTarget.x * deltaVectorFromTowerToTarget.x + deltaVectorFromTowerToTarget.y * deltaVectorFromTowerToTarget.y);
		//This may have better efficiency
		float distance = deltaVectorFromTowerToTarget.x > deltaVectorFromTowerToTarget.y ? deltaVectorFromTowerToTarget.x : deltaVectorFromTowerToTarget.y; // Max(x,y)
		float Second = distance / _speed;

		targetPosition = theTarget->getPositionAfter(Second);

		bulletDirection = targetPosition - towerPostion;
		distance = abs(abs(bulletDirection.x) > abs(bulletDirection.y) ? bulletDirection.x : bulletDirection.y);//Tim max giua x va y
		Second = distance / _speed;
		timeBeforeCollide = Second;//Pre - calc time before collide
		bulletDirection /= Second;//Tinh van toc co huong cho tung frame di chuyen
		bulletSprite.setPosition(towerPostion);
	}
}

void bullet::Update(float deltaTime) {
	sf::Vector2f bulletPosition = bulletSprite.getPosition();
	bulletPosition += bulletDirection * deltaTime;
	timeBeforeCollide -= deltaTime;
	bulletSprite.setPosition(bulletPosition);
}

void bullet::draw(sf::RenderWindow& window) {
	window.draw(bulletSprite);
}

