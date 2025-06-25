#pragma once
#include "point.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>

using namespace std;

class enemy
{
private:
	//Atribute of enemy
	int _speed;
	//int _health;

	/*point _start, _end, _curr;*/
	std::vector<sf::Sprite> sprite;

	//Mảng đường đi của con enemy đã tính trước
	vector<sf::Vector2f> _path;

	//Animation
	std::vector<sf::Texture> textures;
	int currentWayPoint = 0;

	int currentFrame = 0;
	float speed = 50.0F;
	float frameTime = 0.5F;
	float timeSinceLastFrame = 0.0F;
	int totalFrame = 4;


	int dd[4], dc[4];
public:
	enemy();
	enemy(const vector<sf::Vector2f>& _rpath);
	//enemy(point tstart, point tend, point tcurr);
	
	vector<sf::Vector2f> getP() { return _path; }
	//point getStart() { return _start; }
	//point getEnd() { return _end; }
	//point getCurr() { return _curr; }
	int getSpeed() { return _speed; }
	
	void setSeed(int tspeed) {
		if (tspeed > 0) _speed = tspeed; // Có thể cập nhật điều của tốc độ enemy sau
	}
	void setTotalFrame(int rTotalFrame) { totalFrame = rTotalFrame; }

/////////For Animation//////////////////
	void LoadTexture();
	void move(float);
	void animate(float);

public:
	void Update(float);
	void draw(sf::RenderWindow& window);
/////////For Animation //////////////////
};


