//#pragma once
//#include "point.h"
//
//class bullet
//{
//	////_n là độ dài đường đi (số phần tử trong mảng _p)
//	//int _n, _speed; //_n is the number of point for the bullet (số lượng phần tử cho bản đồ mà viên đạn đi)
//	//point _p[point::Map_Game_SIZE * point::Map_Game_SIZE];//Bản đồ mà viên đạn đi
//
//	//point _m[point::Map_Game_SIZE][point::Map_Game_SIZE]; //bản đồ mà viên đạn đang sử dụng trong trục x,y
//	//point curr; //vị trí hiện tại của viên đạn
//
//public:
//	bullet();
//	void UpdateMap_Game(int, int, point);
//
//	point getCurr() { return curr; }
//
//	//Bản đồ viên đạn đi
//	point* getP() { return _p; }
//	int getSpeed() { return _speed; }
//	int getN() { return _n; }
//
//	void setCurr(point tcurr) {
//		//if sẽ có một if để check điều kiện của viên đạn (bay ra khỏi Map_Game...)
//		curr = tcurr;
//	}
//	
//	void setN(int tn){
//		//sẽ có một điều kiện nào đó ở đây
//		_n = tn;
//		}
//
//	void setSpeed(int tspeed) {
//		//điều kiện nào đó cho tốc độ viên đạn
//		_speed = tspeed;
//	}
//	
//	int queryCFromRowCol(int, int);
//	int calcPathBullet(point);
//
//};
//
