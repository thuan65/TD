#pragma once
#include "PlayState.h"
#include "gameSate.h"
#include <string>
#include <fstream> //For reading and writing file

class PlayState; //Forward declaration

class GameSaver {
private:
	static PlayState* currentPlayState;

public:

	static void setPlayState(PlayState* playState);
	static void saveGame(std::ostream& fileOut);//call to save game
	

};

