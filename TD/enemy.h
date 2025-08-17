#pragma once
#include "Resource_Management.h"
#include <vector>
#include <iostream>

using namespace std;

enum class EnemyState {
	Walk,
	Hurt,
	Dead
};

class enemy {
private:

	std::vector<sf::Texture> textures;//This is for moving (Default textures)
	std::vector<sf::Texture> hurt_textures;
	std::vector<sf::Texture> dead_textures;

	sf::Sprite Enemysprite;

	std::string enemyType;
	EnemyState enemyState = EnemyState::Walk; //The normal State of enemy

	//Atribute of enemy
	float _speed;
	int _health;
	int maxHealth; // Lưu lượng máu tối đa(dùng để tính % máu còn lại)
	int bounty; // Biến lưu tiền thưởng khi diệt quái
	sf::RectangleShape healthBarBackground; // Thanh nền màu đỏ
	sf::RectangleShape healthBarForeground; // Thanh máu xanh lá

	//Mảng đường đi của con enemy đã tính trước
	vector<sf::Vector2f> _path;
	int currentWayPoint = 0;//Index của Path

	////////////Animation_helper//////////
	int currentFrame = 0;
	int DeadCurrentFrame = 0;
	float frameTime = 0.15F;
	float walkFrameTime = 0.10f;
	float hurtFrameTime = 0.10f;
	float deadFrameTime = 0.15f;
	float timeSinceLastFrame = 0.0F;
	int totalFrame;
	float durationOfHurtAnimation = 0.025;
	float durationOfDeadtAnimation = 0.15;
	float hurtTimer = 0.0f;//Thời gian từ lúc phát animation
	bool deadAnimationFinished = false;
	bool LastHurtAnimation = false;
	void addAnimation();
	void playLastAnimation(float deltaTime);//Dead animation before delete

	////////////////////////////////////


public:
	enemy(const std::vector<sf::Texture>&, const vector<sf::Vector2f>& _rpath, std::string enemyType, int rMaxHealth = 100, float rspeed = 50.0F, int rBounty = 0.0); 
	enemy(const std::vector<sf::Texture>&, const vector<sf::Vector2f>& _rpath, std::string enemyType, int rMaxHealth, int rHealth ,float rspeed, int rBounty, float x, float y, int currentWayPoint);// Thêm rHealth
	enemy(const std::vector<sf::Texture>&, const std::vector<sf::Texture>& hurt_texture, const std::vector<sf::Texture>& dead_texture, const vector<sf::Vector2f>& _rpath, int rMaxHealth, float rspeed = 50.0F, int rBounty = 0.0);



	vector<sf::Vector2f> getP() { return _path; }
	float getSpeed() { return _speed; }
	int getCurrentWayPoint() { return currentWayPoint; }
	sf::Vector2f getPosition() { return Enemysprite.getPosition(); }

	void setCurrentWayPoint(int rCurrentWayPoint) { currentWayPoint = currentWayPoint; }
	void getEnemyType(const std::string& renemyType) { enemyType = renemyType; }
	void setPosition(sf::Vector2f rPosition) {  Enemysprite.setPosition(rPosition); }
	void setSeed(float tspeed) {
		if (tspeed > 0) _speed = tspeed;
	}
	void setTotalFrame(int rTotalFrame) {
		totalFrame = rTotalFrame;
	}

	sf::Vector2f getPositionAfter(float time);
	void damageTake(int rdamage);
	bool isEnemyAlive();
	int getBounty() const { return bounty; }

	//////////////////////For_Animation///////////////////
	void move(float);
	void animate(float);
	void Update(float);
	void draw(sf::RenderWindow& window);
	
	//////////////////////For_Animation///////////////////

	bool reachedEnd(); //Enemy reached ended ?


	std::string getEnemyType() { return enemyType; }
	int getMaxHealth() { return maxHealth; }
	int getHealth() { return _health; }
	int getBounty() { return bounty; }

	void setEnemyType(std::string renemyType) { enemyType = renemyType; }
	void setMaxHealth(int rmaxHealth) {  maxHealth = rmaxHealth; }
	void setSpeed(float rspeed) {  _speed = rspeed; }
	void setHealth(int rhealth) {  _health = rhealth; }
	void setBounty(int rbounty) {  bounty = rbounty; }

};


