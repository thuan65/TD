#pragma once
#include "bullet.h"

class tower
{
	point _location; //This is location of the tower
	bullet _b;//Cái viên đạn mà tháp bắn ra

public:
	tower() { _location = { 0,0,0 }; }
	point getLocation() { return _location; }
	void setLocation(point tlocation) {
		//
		_location = tlocation;
	}
	void setMapForBullet(point[][point::MAP_SIZE]);
	void calcPathBullet() {
		_b.calcPathBullet(_location);
	}

	bullet& getBullet() { return _b; }
};

