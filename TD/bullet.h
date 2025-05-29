#pragma once
#include "point.h"

class bullet
{
	//_n là độ dài đường đi (số phần tử trong mảng _p)
	int _n, _speed;
	point _p[point::MAP_SIZE * point::MAP_SIZE];

	point _m[point::MAP_SIZE][point::MAP_SIZE]; //bản đồ mà viên đạn đang sử dụng trong trục x,y
	point curr; //vị trí hiện tại của viên đạn

public:
	bullet();
	void UpdateMap(int, int, point);

	point getCurr() { return curr; }
	point* getP() { return _p; }
	int getSpeed() { return _speed; }
	int getN() { return _n; }

	void setCurr(point tcurr) {
		//if sẽ có một if để check điều kiện của viên đạn (bay ra khỏi map...)
		curr = tcurr;
	}
	
	void setN(int tn){
		//sẽ có một điều kiện nào đó ở đây
		_n = tn;
		}

	void setSpeed(int tspeed) {
		//điều kiện nào đó cho tốc độ viên đạn
		_speed = tspeed;
	}
	
	int queryCFromRowCol(int, int);
	int calcPathBullet(point);

};

