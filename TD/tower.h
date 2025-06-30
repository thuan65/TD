#pragma once
#include "bullet.h"
#include "SFML/Graphics.hpp"
#include <vector>

class tower {
	std::vector<sf::Texture> towerTexture;
	sf::Sprite towerSprite;

	point _location; //This is location of the tower
	bullet _b;//Cái viên đạn mà tháp bắn ra

public:
	tower(const std::vector<sf::Texture>& rtowerTexture, int row = 0, int col = 0);
	void draw(sf::RenderWindow& window);

	point getLocation() { return _location; }
	void setLocation(const point tlocation) {
		//
		_location = tlocation;
		towerSprite.setPosition(sf::Vector2f(_location.getX() * point::TileSize, _location.getY() * point::TileSize));
	}
	void setMap_GameForBullet(point[][point::Map_Game_SIZE]);
	void calcPathBullet() {
		_b.calcPathBullet(_location);
	}

	bullet& getBullet() { return _b; }
};

