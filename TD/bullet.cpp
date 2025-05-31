#include "bullet.h"

bullet::bullet() {
	_n = 0; 
	_speed = 4;
	curr = { 0, 0,0 };
	for (int i = 0; i < point::MAP_SIZE * point::MAP_SIZE; i++) {
		_p[i] = { 0,0,0, };
	}

	for(int i = 0; i < point::MAP_SIZE; i++) {
		for (int j = 0; j < point::MAP_SIZE; j++) {
			_m[i][j] = { 0,0,0 };
		}
	}
}

void bullet::UpdateMap(int i, int j, point v) {
	// we have some if() here
	_m[i][j] = v;
}

//Lấy cái vị trí tiếp theo mà viên đạn bay
int bullet::queryCFromRowCol(int row, int col) {
	if (row < 0 || row >= point::MAP_SIZE || col < 0 || col >= point::MAP_SIZE) return -2;
	//Nếu không hợp lệ thì trả về -2

	for (int i = 0; i < point::MAP_SIZE; i++) {
		for (int j = 0; j < point::MAP_SIZE; j++) {
			point tmp = point::fromXYtoRowCol(_m[i][j]);
			if (tmp.getX() == row && tmp.getY() == col) {
				return _m[i][j].getC();
			}
		}
	}
}

int bullet::calcPathBullet(point tower) {
	point tmp = point::fromXYtoRowCol(tower);
	int row = tmp.getX(), col = tmp.getY(), i = 0;

	do {
		col++; row--;
		if (queryCFromRowCol(row, col) == 0) {//Kiểm tra đường đi có đi được không (0 là trống)
			_p[i] = point::fromRowColtoXY({ row, col, 0 });
			i += 2;
		}
		else break;
	} while (i < point::MAP_SIZE);
	_n = i;
	for (i = 1; i < _n; i +=2) {
		_p[i] = { _p[i - 1].getX() + 2, _p[i - 1].getY() - 1, 0 };
	}

	curr = { _p[0].getX(), _p[0].getY(), _p[0].getC() };
	return _n;
}
