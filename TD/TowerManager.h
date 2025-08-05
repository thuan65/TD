#pragma once
#include "tower.h"
#include "enemy.h"
#include "BulletManager.h"
#include "Resource_Management.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

class TowerManager{

private: 
	sf::RenderWindow* window; // Giả sử bạn có một cửa sổ để vẽ

	struct buildZone {
		sf::FloatRect bounds;
		bool TowerExist = false;
	};
	
	BulletManager* bulletManager;
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

	sf::Vector2f theTowerPosition; // Vị trí của tháp

public:

	// Hàm trợ giúp để thiết lập các đối tượng menu
	void setupBuildMenu();
	void openBuildMenu(int row, int col);
	void closeBuildMenu();

	TowerManager(sf::RenderWindow* window,BulletManager* rbulletManager = nullptr);
	~TowerManager();

	void update(float deltaTime, std::vector<enemy*>& enemies);//Kiem soat viec dan ban
	bool towerTowerExisted(sf::Vector2f worldPos);
	bool towerTowerExisted(const buildZone& zone);//Check to see if tower exist in some Title
	void ReadFile(const std::string& filePath);
	bool buildTower(sf::Vector2f worldPos, std::string towerType);
	bool clickCheck(sf::Vector2f worldPos);//Is this a build zone
	void resolveTowerAt(sf::Vector2f worldPos, int& money); //Giải quyết việc xây tháp / nâng cấp tháp, bán tháp
	void reset();
	void sellTower();
	void upgrateTower();

	void draw(sf::RenderWindow& window);
};

