#pragma once
#include "mapTowerDefense_Game.h"
#include "WaveManager.h" //For mapSelection
#include "mapManager.h"
#include "BulletManager.h"
#include "TowerManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Resource_Management.h"
#include "PathFinder.h"
#include <iostream>
#include <memory>

namespace sf {
    class Sprite;
}

class game {
private:
    sf::RenderWindow window;
    mapTowerDefense_Game gameMap;
    BulletManager bulletManager;
    WaveManager waveControl;
    TowerManager towerControl;
    mapManager mapSelection;

    int lives;
    int money;
    int currentWave;
    bool isGameOver;
    bool playerWon;


    bool isBuildMenuOpen;
    sf::Vector2i buildMenuTilePosition; // Lưu vị trí (row, col) của ô đang mở menu

    // Các đối tượng đồ họa cho menu
    // Giả sử menu là một hình chữ nhật đơn giản chứa 2 icon
    std::unique_ptr<sf::RectangleShape> buildMenuBackground;
    std::unique_ptr<sf::Sprite> buildMenuTower1Icon;
    std::unique_ptr<sf::Sprite> buildMenuTower2Icon;
    std::unique_ptr<sf::Sprite> buildMenuTower3Icon; // << THÊM
    std::unique_ptr<sf::Sprite> buildMenuTower4Icon; // << THÊM

    std::vector<sf::Sprite> livesSprites;
    std::vector<sf::Sprite> moneySprites;
    std::vector<sf::Sprite> waveSprites;
    std::unique_ptr<sf::Sprite> gameOverSprite; // Ảnh "Game Over"
    std::unique_ptr<sf::Sprite> victorySprite;  // Ảnh "Victory"


    bool isBetweenWaves; // Cờ báo hiệu đang trong thời gian nghỉ
    float timeUntilNextWave; // Thời gian đếm ngược

    // Hằng số thời gian nghỉ giữa các wave
    const float TIME_BETWEEN_WAVES = 3.0f; // 3 giây    

    // ... các unique_ptr ...
    std::unique_ptr<sf::Text> victoryText;
    std::vector<sf::Sprite> nextWaveTimerSprites;


    // Vùng có thể click của các icon
    //sf::FloatRect tower1IconBounds;
    //sf::FloatRect tower2IconBounds;
    //sf::FloatRect tower3IconBounds; // << THÊM
    //sf::FloatRect tower4IconBounds; // << THÊM

    // Hàm trợ giúp để thiết lập các đối tượng menu
    void setupBuildMenu();
    void openBuildMenu(int row, int col);
    void closeBuildMenu();
    void updateGUISprites();
    void drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector);

public:
    game();
    ~game();
    void Run();
};