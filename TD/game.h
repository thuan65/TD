//#pragma once
//#include "mapTowerDefense_Game.h"
//#include "WaveManager.h" //For mapSelection
//#include "mapManager.h"
//#include "BulletManager.h"
//#include "TowerManager.h"
//#include "SFML/Graphics.hpp"
//#include "SFML/Window.hpp"
//#include "Resource_Management.h"
//#include "gameSate.h"
//#include "GameSaver.h"
//#include "PathFinder.h"
//#include <iostream>
//#include <memory>
//
//namespace sf {
//    class Sprite;
//}
//
//class game {
//private:
//    sf::RenderWindow window;
//    mapTowerDefense_Game gameMap;
//    WaveManager waveControl;
//    BulletManager bulletManager;
//    TowerManager towerControl;
//    mapManager mapSelection;
//   
//
//    int lives;
//    int money;
//    int currentWave;
//    bool isGameOver;
//    bool playerWon;
//
//  
//
//    std::vector<sf::Sprite> livesSprites;
//    std::vector<sf::Sprite> moneySprites;
//    std::vector<sf::Sprite> waveSprites;
//    //std::unique_ptr<sf::Sprite> gameOverSprite; // Ảnh "Game Over"
//   // std::unique_ptr<sf::Sprite> victorySprite;  // Ảnh "Victory"
//
//
//    bool isBetweenWaves; // Cờ báo hiệu đang trong thời gian nghỉ
//    float timeUntilNextWave; // Thời gian đếm ngược
//
//    // Hằng số thời gian nghỉ giữa các wave
//    const float TIME_BETWEEN_WAVES = 3.0f; // 3 giây    
//
//    // ... các unique_ptr ...
//    //std::unique_ptr<sf::Text> victoryText;
//    std::vector<sf::Sprite> nextWaveTimerSprites;
//
//
//    // Vùng có thể click của các icon
//    //sf::FloatRect tower1IconBounds;
//    //sf::FloatRect tower2IconBounds;
//    //sf::FloatRect tower3IconBounds; // << THÊM
//    //sf::FloatRect tower4IconBounds; // << THÊM
//
//  
//    void updateGUISprites();
//    void drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector);
//
//    //BulletManager& getBulletManager() { return bulletManager; }
//  
//
//public:
//
//    void handleWaveTiming(float deltaTime);
//    void handleEnemyResults();
//
//    WaveManager& getWaveManager() { return waveControl; }
//    TowerManager& getTowerManager() { return towerControl; }
//    mapManager& getMapManager() { return mapSelection; }
//
//    int getLives() { return lives; }
//    int getMoney() { return money; }
//    int getCurrentWave() { return currentWave; }
//    bool getIsGameOver() { return isGameOver; }
//    bool getPlayerWon() { return playerWon; }
//
//    void setLives(int rlives) {  lives = rlives; }
//    void setMoney(int rmoney) {  money = rmoney; }
//    void setCurrentWave(int rcurrentWave) {  currentWave = rcurrentWave; }
//    void setIsGameOver(bool risGameOver) {  isGameOver = risGameOver; }
//    void setPlayerWon(bool rplayerWon) {  playerWon = rplayerWon; }
//
//    game();
//    ~game();
//    void Run();
//    
//};
//

#pragma once

#include <memory>
#include <stack>
#include <vector>
#include "SFML/Graphics.hpp"
#include "State.h"
#include "MainMenuState.h"
#include "Resource_Management.h"


class game {

public:
	game();
	~game();

	void run();

	//void pushState(std::unique_ptr<State> stats);
	//void popState();
	//void changeState(std::unique_ptr<State> states);

private:
	void initResources();
	void initWindow();
	void initStates();

	void handleEvents();
	void update(float dt);
	void render();

private:
	sf::RenderWindow window;
	std::stack<std::unique_ptr<State>> states;
	sf::Clock dtClock;

private:
	void initMainMenuState();
};


