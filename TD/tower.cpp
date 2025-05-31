#include "tower.h"

void tower::setMapForBullet(point a[][point::MAP_SIZE]) {//Update map dữa trên cái map mình tạo ra
	for (int i = 0; i < point::MAP_SIZE; i++) {
		for (int j = 0; j < point::MAP_SIZE; j++) {
			_b.UpdateMap(i, j, a[i][j]);//Cập nhật đường đi cho viên đạn
		}
	}
}