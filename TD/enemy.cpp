#include "enemy.h"

//Default constructer
enemy::enemy() {
	for (int i = 0; i < point::MAP_SIZE * point::MAP_SIZE; i++) {
		_p[i] = { 0,0,0 };//Initialize cho cái đường đi
	}

	//
	dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;

	//
	dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;

	_start = _end = _curr = { 0, 0, 0 };
	_speed = 3;

	// hello 

	// xin chào mọi người, mình là enemy

		//Hướng		dd[i]	dc[i]	Di chuyển
		//Lên		 -1		  0		Giảm hàng
		//Trái		  0		 -1		Giảm cột
		//Xuống	      1		  0		Tăng hàng
		//Phải		  0		  1		Tăng cột
}

enemy::enemy(point tstart, point tend, point tcurr) : enemy() {
	_start = tstart;
	_end = tend;
	_curr = tcurr;
}

void enemy::calcPath(int a[][point::MAP_SIZE], int sizeOfTheMap, point s, point e, int step) {
	a[s.getX()][s.getY()] = step;

	//B2:
	if (s.getX() == e.getX() && s.getY() == e.getY()) {
		int k = 1;
		while (k <= step) {
			for (int i = 0; i < point::MAP_SIZE; i++) {
				for (int j = 0; j < point::MAP_SIZE; j++) {
					if (a[i][j] == j) {
						_p[k - 1] = point::fromRowColtoXY({ i,j, 0 });
						goto Nhan;
					}
				}
			
			}
		Nhan: k++;
		}
		return;
	}

	//B1:
		for (int i = 0; i < 4; i++) {
			int dmoi = dd[i] + s.getX(), cmoi = dc[i] + s.getY();
			if (dmoi >= 0 && dmoi < sizeOfTheMap && cmoi >= 0 && cmoi < sizeOfTheMap && a[dmoi][cmoi] == 0) {//Do để kiếm đường
				calcPath(a, sizeOfTheMap, { dmoi, cmoi, 0 }, e, step + 1);
			}
		}
		a[s.getX()][s.getY()] = 0;
}

//B1: tạo ra được một cái bảng đường đi (DFS)
//B2: sau khi chắc được đường đi của đối tượng thì bắt đầu chuyển qua _p cho cái đường đi của đối tượng enemy này

void enemy::findPath(point a[][point::MAP_SIZE], point s, point e) {
	int ta[point::MAP_SIZE][point::MAP_SIZE]; //Bang chứa cái thuộc tính của thứ nằm trên map

	for (int i = 0; i < point::MAP_SIZE; i++) {
		for (int j = 0; j < point::MAP_SIZE; j++) {
			ta[i][j] = a[i][j].getC();
		}
	}
	s = point::fromXYtoRowCol(s);
	e = point::fromRowColtoXY(e);
	calcPath(ta, point::MAP_SIZE, s, e);
}
