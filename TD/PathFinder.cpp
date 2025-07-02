#include "PathFinder.h"
#include <iostream>

//Hướng		dd[i]	dc[i]	Di chuyển
//Lên		 -1		  0		Giảm hàng
//Trái		  0		 -1		Giảm cột
//Xuống	      1		  0		Tăng hàng
//Phải		  0		  1		Tăng cột

//static memeber definitions
point PathFinder::_start;
point PathFinder::_curr;
point PathFinder::_end;

std::vector<sf::Vector2f> PathFinder::_path;

int PathFinder::dd[4] = { -1, 0, 1, 0 };
int PathFinder::dc[4] = { 0, -1, 0, 1 };

void PathFinder::findPath(std::vector<std::vector<point>> a) {
	_path.clear();

	//Bang chứa cái thuộc tính của thứ nằm trên Map_Game
	std::vector<std::vector<int>> ta;

	ta.resize(a.size(), std::vector<int>(a[0].size()));

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++) {
			ta[i][j] = a[i][j].getC();
		}
	}
	point s, e;
	s = _start;
	e = _end;

	calcPath(ta, s, e);
}

//B1: tạo ra được một cái bảng đường đi (DFS)
//B2: sau khi chắc được đường đi của đối tượng thì bắt đầu chuyển qua _p cho cái đường đi của đối tượng enemy này

void PathFinder::calcPath(std::vector<std::vector<int>> a, point s, point e, int step) {
	a[s.getX()][s.getY()] = step;

	//B2: check thuat toan DFS hoan thanh? (if yes) luu _path cho enemy
	if (s.getX() == e.getX() && s.getY() == e.getY()) {
	
		int k = 1; 
		while (k <= step) {
			for (int i = 0; i < a.size(); i++) {
				for (int j = 0; j < a[0].size(); j++) {
					if (a[i][j] == k) {
						_path.emplace_back(sf::Vector2f{ (float)j * point::TileSize, (float)i * point::TileSize}); //(X,Y) 
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
		if (dmoi >= 0 && dmoi < a.size() && cmoi >= 0 && cmoi < a[0].size() && a[dmoi][cmoi] == 0) {//Do để kiếm đường
			calcPath(a, { dmoi, cmoi, 0 }, e, step + 1);
		}
	}
	a[s.getX()][s.getY()] = 0;
}



