#pragma once
#include "tower.h"
#include "enemy.h"
#include "BulletManager.h"
#include "Resource_Management.h"
#include "WaveManager.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>


// Hằng số giá tiền (đặt ở đây hoặc file config chung)
const int TOWER1_COST = 100;
const int TOWER2_COST = 150;
const int TOWER3_COST = 200;
const int TOWER4_COST = 250;

class WaveManager;

class TowerManager{

private: 
	sf::RenderWindow* window; // Giả sử bạn có một cửa sổ để vẽ

	struct buildZone {
		sf::FloatRect bounds;
		bool TowerExist = false;
	};

	std::vector<sf::Sprite> tower1CostSprites;
	std::vector<sf::Sprite> tower2CostSprites;
	std::vector<sf::Sprite> tower3CostSprites;
	std::vector<sf::Sprite> tower4CostSprites;
	
	BulletManager* bulletManager;
	WaveManager* waveControl;
	std::vector<tower*> towers;
	std::vector<buildZone> buildZones;

	bool isBuildMenuOpen;
	sf::Vector2i buildMenuTilePosition; // Lưu vị trí (row, col) của ô đang mở menu

	// Các đối tượng đồ họa cho menu
	// Giả sử menu là một hình chữ nhật đơn giản chứa 2 icon
	std::unique_ptr<sf::RectangleShape> buildMenuBackground;
	std::unique_ptr<sf::Sprite> buildMenuTower1Icon;
	std::unique_ptr<sf::Sprite> buildMenuTower2Icon;
	std::unique_ptr<sf::Sprite> buildMenuTower3Icon; // << THÊM
	std::unique_ptr<sf::Sprite> buildMenuTower4Icon; // << THÊM


	std::vector<sf::Sprite> costSprites;

	sf::Vector2f theTowerPosition; // Vị trí của tháp
	void drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector);

	bool isUpgradeMenuOpen;
	tower* selectedTower; // Con trỏ tới trụ đang được chọn
	std::unique_ptr<sf::RectangleShape> upgradeMenuBackground;
	std::unique_ptr<sf::Sprite> upgradeButtonIcon;
	std::unique_ptr<sf::Sprite> sellButtonIcon;

public:

	// Hàm trợ giúp để thiết lập các đối tượng menu
	void setupBuildMenu();
	void openBuildMenu(int row, int col);
	void closeBuildMenu();

	TowerManager(sf::RenderWindow* window,BulletManager* rbulletManager = nullptr, WaveManager* waveControl = nullptr);
	~TowerManager();

	void update(float deltaTime);//Thap check co enemy trong tam ban
	bool towerTowerExisted(sf::Vector2f worldPos);
	bool towerTowerExisted(const buildZone& zone);//Check to see if tower exist in some Title
	void ReadFile(const std::string& filePath);
	bool buildTower(sf::Vector2f worldPos, std::string towerType);
	bool clickCheck(sf::Vector2f worldPos);//Is this a build zone
	void resolveTowerAt(sf::Vector2f worldPos, int& money); //Giải quyết việc xây tháp / nâng cấp tháp, bán tháp
	void reset();
	void sellTower();
	void upgrateTower();

	void setWaveManager(WaveManager* manager);

	void draw(sf::RenderWindow& window);
	void openUpgradeMenu(tower* targetTower);
	void closeUpgradeMenu();
};

