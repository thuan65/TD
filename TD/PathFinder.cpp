#include "PathFinder.h"

//static memeber definitions
point PathFinder::_start;
point PathFinder::_curr;
point PathFinder::_end;

std::vector<sf::Vector2f> PathFinder::_path;

int PathFinder::dd[4] = { -1, 0, 1, 0 };
int PathFinder::dc[4] = { 0, -1, 0, 1 };

void PathFinder::findPath(point a[][point::MAP_SIZE], point s, point e) {
	int ta[point::MAP_SIZE][point::MAP_SIZE]; //Bang chứa cái thuộc tính của thứ nằm trên map

	for (int i = 0; i < point::MAP_SIZE; i++) {
		for (int j = 0; j < point::MAP_SIZE; j++) {
			ta[i][j] = a[i][j].getC();
		}
	}
	s = point::fromXYtoRowCol(s);
	e = point::fromXYtoRowCol(e);
	calcPath(ta, point::MAP_SIZE, s, e);
}

void PathFinder::calcPath(int a[][point::MAP_SIZE], int sizeOfTheMap, point s, point e, int step) {
	a[s.getX()][s.getY()] = step;

	//B2: check thuat toan DFS hoan thanh? (if yes) luu _path cho enemy
	if (s.getX() == e.getX() && s.getY() == e.getY()) {
		int k = 1;
		while (k <= step) {
			for (int i = 0; i < point::MAP_SIZE; i++) {
				for (int j = 0; j < point::MAP_SIZE; j++) {
					if (a[i][j] == k) {
						_path.emplace_back(sf::Vector2f{ (float)j, (float)i }); //(X,Y) 
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



