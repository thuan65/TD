#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "Sprite.h"
#include "PauseState.h"
#include "VictoryState.h"
#include "LoseState.h"
#include "gameSate.h"
#include "mapTowerDefense_Game.h"
#include "WaveManager.h" //For mapSelection
#include "mapManager.h"
#include "BulletManager.h"
#include "TowerManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "GameSaver.h"
#include "PathFinder.h"
#include <iostream>
#include <memory>
#include <stack>

//namespace sf {
//	class Sprite;
//}

class PlayState : public State {

public:
	PlayState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, MapID mapID);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;

private:
	MapID currentMap;
	float timeAccumulator = 0.0f;
	int currentFrame = 0;

	//Sprite backgroundSprite;
	Sprite pauseIconSprite = Sprite(Resource_Management::pauseIconTexture, { 518, 24 });

private:
	//static const sf::Texture& getBackgroundTexture(MapID mapID, int index = 0);
	mapTowerDefense_Game gameMap;
	WaveManager waveControl;
	BulletManager bulletManager;
	TowerManager towerControl;
	mapManager mapSelection;

	int lives;
	int money;
	int currentWave;
	bool isGameOver;
	bool playerWon;

	std::vector<sf::Sprite> livesSprites;
	std::vector<sf::Sprite> moneySprites;
	std::vector<sf::Sprite> waveSprites;

	bool isBetweenWaves; // Cờ báo hiệu đang trong thời gian nghỉ
	float timeUntilNextWave; // Thời gian đếm ngược

	// Hằng số thời gian nghỉ giữa các wave
	const float TIME_BETWEEN_WAVES = 3.0f; // 3 giây    

	std::vector<sf::Sprite> nextWaveTimerSprites;
	void updateGUISprites();
	void drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector);

public:

	void handleWaveTiming(float deltaTime);
	void handleEnemyResults();

	WaveManager& getWaveManager() { return waveControl; }
	TowerManager& getTowerManager() { return towerControl; }
	mapManager& getMapManager() { return mapSelection; }

	int getLives() { return lives; }
	int getMoney() { return money; }
	int getCurrentWave() { return currentWave; }
	bool getIsGameOver() { return isGameOver; }
	bool getPlayerWon() { return playerWon; }

	void setLives(int rlives) { lives = rlives; }
	void setMoney(int rmoney) { money = rmoney; }
	void setCurrentWave(int rcurrentWave) { currentWave = rcurrentWave; }
	void setIsGameOver(bool risGameOver) { isGameOver = risGameOver; }
	void setPlayerWon(bool rplayerWon) { playerWon = rplayerWon; }

};

