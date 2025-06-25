#pragma once
class point {
public:
	const static int MAP_SIZE = 10;
	const static int LEFT = 3;
	const static int TOP = 1;

	const static int TileSize = 32;

private:
	int x, y, c;

public:
	point() { x = y = c = 0; }
	point(int tx, int ty, int tc) { x = tx, y = ty, c = tc; }
	int getX() { return x; }
	int getY() { return y; }
	int getC() { return c; }
	void setC(int tc) { c = tc; }
	static point fromXYtoRowCol(point v);
	static point fromRowColtoXY(point s);
};

