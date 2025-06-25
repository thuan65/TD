#pragma once
#include "point.h"
#include <vector>
#include "SFML\Graphics.hpp"

class PathFinder {
	PathFinder() {};
private:
	static std::vector<sf::Vector2f> _path;
	static point _start, _end, _curr;

	static int dd[4], dc[4];
public:

	inline static void setStart(const point& tstart) {
		//sẽ có một điều kiện về vị trí enemy xuất hiện, sau này if cần
		_start = tstart;
	}
	inline static void setEnd(const point& tend) {
		//giống start, sẽ có điều kiện tại chỗ này
		_end = tend;
	}
	inline static void setCurr(const point& tcurr) {
		//giống start
		_curr = tcurr;
	}

	static void findPath(std::vector<std::vector<point>>, point, point);
	static const std::vector<sf::Vector2f>& getPath() { return _path; }
private:
	static void calcPath(std::vector<std::vector<int>>, int, point, point, int = 1);

};

