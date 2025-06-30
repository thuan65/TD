#pragma once
#include "point.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class enemy
{
private:

	std::vector<sf::Texture> textures;
	sf::Sprite Enemysprite;

	//Atribute of enemy
	float _speed;
	//int _health;

	//Mảng đường đi của con enemy đã tính trước
	vector<sf::Vector2f> _path;

	////////////Animation_helper//////////
	int currentWayPoint = 0;
	int currentFrame = 0;
	float frameTime = 0.5F;
	float timeSinceLastFrame = 0.0F;
	int totalFrame = 4;


public:
	//enemy();
	enemy(const std::vector<sf::Texture>& ,const vector<sf::Vector2f>& _rpath, float rspeed = 50.0F);
	
	vector<sf::Vector2f> getP() { return _path; }
	int getSpeed() { return _speed; }
	
	void setSeed(int tspeed) {
		if (tspeed > 0) _speed = tspeed; // Có thể cập nhật điều của tốc độ enemy sau
	}
	void setTotalFrame(int rTotalFrame) { 
		totalFrame = rTotalFrame;
	}

//////////////////////For_Animation///////////////////
	void move(float);								
	void animate(float);								

public:

	void Update(float, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
//////////////////////For_Animation///////////////////
};


