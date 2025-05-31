#pragma once
#include "map.h"

class game {
private:
	map _map;
	bool _ISEXIT1, _ISEXIT2;

public:
	game();
	bool getIsExist1() { return _ISEXIT1; }
	bool getIsExist2() { return _ISEXIT2; }

	void setIsExist1(bool b) { _ISEXIT1 = b; }
	void setIsExist2(bool b) { _ISEXIT2 = b; }
	map& getMap() { return _map; }
	void startGame();
};

