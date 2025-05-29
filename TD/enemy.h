#pragma once
#include "point.h"

class enemy
{
private:
	int _speed;
	point _start, _end, _curr;

	//Mảng đường đi của con enemy đã tính trước
	point _p[point::MAP_SIZE * point::MAP_SIZE];
	int dd[4], dc[4];
public:
	enemy();
	enemy(point tstart, point tend, point tcurr);
	
	point* getP() { return _p; }
	point getStart() { return _start; }
	point getEnd() { return _end; }
	point getCurr() { return _curr; }
	int getSpeed() { return _speed; }
	
	void setSeed(int tspeed) {
		if (tspeed > 0) _speed = tspeed; // Có thể cập nhật điều của tốc độ enemy sau
	}
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
	void findPath(point[][point::MAP_SIZE], point, point);
private:
	void calcPath(int[][point::MAP_SIZE], int, point, point, int = 1);

};

