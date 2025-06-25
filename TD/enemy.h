#pragma once
#include "point.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>

using namespace std;

class enemy
{
private:


	///Atribute of enemy 
	int healt;
	int _speed;
	/// (cac thuoc tinh tong quat cua enemy)

	//Mảng đường đi của con enemy đã tính trước
	vector<sf::Vector2f> _path;
	//point _p[point::MAP_SIZE * point::MAP_SIZE];

	point _start, _end, _curr;

	int dd[4], dc[4];
public:
	enemy();
	enemy(const vector<sf::Vector2f>& _rpath);
	enemy(point tstart, point tend, point tcurr);
	
	vector<sf::Vector2f> getP() { return _path; }
	point getStart() { return _start; }
	point getEnd() { return _end; }
	point getCurr() { return _curr; }
	int getSpeed() { return _speed; }
	
	void setSeed(int tspeed) {
		if (tspeed > 0) _speed = tspeed; // Có thể cập nhật điều của tốc độ enemy sau
	}

//////////////////////
	void setStart(point tstart) {
		//sẽ có một điều kiện về vị trí enemy xuất hiện, sau này if cần
		_start = tstart;
	}
	void setEnd(point tend) {
		//giống start, sẽ có điều kiện tại chỗ này
		_end = tend;
	}
	void setCurr(point tcurr) {
		//giống start
		_curr = tcurr;
	}
/////////////////////////

	void findPath(point[][point::MAP_SIZE], point, point);
private:
	void calcPath(int[][point::MAP_SIZE], int, point, point, int = 1);

};


