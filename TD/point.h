#pragma once
class point {
public:
	const static int TileSize = 32;
	const static int Empty_Tile = -2; //A empty tile in the map grid
	const static int Path_Tile = 0;  //Path in the map grid
	const static int Wall_Tile = -1;//Not an empty tile in the map grid

private:
	int x, y, c;

public:
	point() { x = y = c = 0; }
	point(int tx, int ty, int tc) { x = tx, y = ty, c = tc; }
	int getX() const { return x; }
	int getY()  const { return y; }
	int getC() const { return c; }
	void setX(int tx) { x = tx; }
	void setY(int ty) { y = ty; }
	void setC(int tc) { c = tc; }
	//static point fromXYtoRowCol(point v);
	//static point fromRowColtoXY(point s);
};

