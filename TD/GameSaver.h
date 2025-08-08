#pragma once
#include "game.h"
#include "gameSate.h"
#include <string>
#include <fstream> //For reading and writing file

class game; //Forward declaration
class mapManager; //For selection map
class WaveManager;//For enemy Save

class GameSaver {
private:
	game* cgame;

public:
	GameSaver(game* cgame = nullptr);
	void saveGame(const string& filePath);
	void loadGame(const string& filePath);


};

