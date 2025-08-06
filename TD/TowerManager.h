//#pragma once
//#include "tower.h"
//#include "enemy.h"
//#include "BulletManager.h"
//#include "Resource_Management.h"
//#include <SFML/Graphics.hpp>
//#include <fstream>
//#include <vector>
//#include <string>
//
//
//// Hằng số giá tiền (đặt ở đây hoặc file config chung)
//const int TOWER1_COST = 100;
//const int TOWER2_COST = 150;
//const int TOWER3_COST = 200;
//const int TOWER4_COST = 250;
//
//
//class TowerManager{
//
//private:
//	sf::RenderWindow* window;
//	BulletManager* bulletManager;
//	std::vector<tower*> towers; // Giữ nguyên tên
//	
//
//	struct buildZone {
//		sf::FloatRect bounds;
//		bool TowerExist = false;
//	};
//
//	std::vector<buildZone> buildZones;
//
//	std::vector<sf::Sprite> tower1CostSprites;
//	std::vector<sf::Sprite> tower2CostSprites;
//	std::vector<sf::Sprite> tower3CostSprites;
//	std::vector<sf::Sprite> tower4CostSprites;
//	
//
//	bool isBuildMenuOpen;
//	sf::Vector2f theTowerPosition; // Vị trí của tháp
//	//tower* m_selectedTower; // Tháp đang được chọn để nâng cấp hoặc bán
//	//sf::Vector2i buildMenuTilePosition; // Lưu vị trí (row, col) của ô đang mở menu
//	//sf::Vector2f m_buildPosition; // Vị trí (pixel) tâm ô để xây trụ mới
//
//	// Các đối tượng đồ họa cho menu
//	// Giả sử menu là một hình chữ nhật đơn giản chứa 2 icon
//	std::unique_ptr<sf::RectangleShape> buildMenuBackground;
//	std::unique_ptr<sf::Sprite> buildMenuTower1Icon;
//	std::unique_ptr<sf::Sprite> buildMenuTower2Icon;
//	std::unique_ptr<sf::Sprite> buildMenuTower3Icon; // << THÊM
//	std::unique_ptr<sf::Sprite> buildMenuTower4Icon; // << THÊM
//
//
//	std::vector<sf::Sprite> costSprites;
//
//	bool isUpgradeMenuOpen;      // << THÊM
//	tower* selectedTower;        // << THÊM
//	std::unique_ptr<sf::RectangleShape> upgradeMenuBackground; // << THÊM
//	std::unique_ptr<sf::Sprite> upgradeButtonIcon;             // << THÊM
//	std::unique_ptr<sf::Sprite> sellButtonIcon;                // << THÊM
//
//	
//	
//	// --- Hàm trợ giúp Private ---
//	void setupMenus(); // << Sửa tên
//	void openBuildMenu(sf::Vector2f position);
//	void closeBuildMenu();
//	void openUpgradeMenu(tower* targetTower);
//	void closeUpgradeMenu();
//	void drawNumber(int number, float x, float y);
//
//
//
//public:
//
//	// Hàm trợ giúp để thiết lập các đối tượng menu
//	
//	TowerManager(sf::RenderWindow* window,BulletManager* rbulletManager = nullptr);
//	~TowerManager();
//
//	//void update(float deltaTime, std::vector<enemy*>& enemies);//Kiem soat viec dan ban
//	//bool towerTowerExisted(sf::Vector2f worldPos);
//	//bool towerTowerExisted(const buildZone& zone);//Check to see if tower exist in some Title
//	//void ReadFile(const std::string& filePath);
//	//bool buildTower(sf::Vector2f worldPos, std::string towerType);
//	//bool clickCheck(sf::Vector2f worldPos);//Is this a build zone
//	//void resolveTowerAt(sf::Vector2f worldPos, int& money); //Giải quyết việc xây tháp / nâng cấp tháp, bán tháp
//	//void reset();
//	//void sellTower();
//	//void upgrateTower();
//
//	//void draw(sf::RenderWindow& window);
//
//	void ReadFile(const std::string& filePath);
//	void update(float deltaTime, std::vector<enemy*>& enemies);
//	void draw(sf::RenderWindow& window);
//	void handleMouseClick(sf::Vector2f worldPos, int& money); // << Hàm xử lý chính mới
//};
//

#pragma once
#include "tower.h"
#include "BulletManager.h"
#include "Resource_Management.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

// Hằng số giá tiền
const int TOWER1_COST = 100;
const int TOWER2_COST = 150;
const int TOWER3_COST = 200;
const int TOWER4_COST = 250;

class TowerManager {
private:
	// --- Liên kết Hệ thống & Dữ liệu ---
	sf::RenderWindow* m_window;
	BulletManager* m_bulletManager;
	std::vector<tower*> m_towers;

	struct buildZone {
		sf::FloatRect bounds;
		bool towerExist = false;
	};
	std::vector<buildZone> m_buildZones;

	// --- Trạng thái & Dữ liệu Menu ---
	bool m_isBuildMenuOpen;
	bool m_isUpgradeMenuOpen;
	tower* m_selectedTower;      // Trụ đang được chọn
	sf::Vector2f m_buildPosition; // Vị trí (pixel) tâm ô để xây trụ mới

	// --- Đối tượng đồ họa Menu ---
	std::unique_ptr<sf::RectangleShape> m_buildMenuBG;
	std::unique_ptr<sf::Sprite> m_buildIcon1, m_buildIcon2, m_buildIcon3, m_buildIcon4;

	std::unique_ptr<sf::RectangleShape> m_upgradeMenuBG;
	std::unique_ptr<sf::Sprite> m_upgradeIcon, m_sellIcon;
	std::vector<sf::Sprite> m_costSprites; // Dùng chung cho cả 2 menu

	// --- Hàm trợ giúp Private ---
	void setupMenus();
	void openBuildMenu(sf::Vector2f position);
	void closeBuildMenu();
	void openUpgradeMenu(tower* targetTower);
	void closeUpgradeMenu();
	void drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector);
	bool buildTower(int row, int col, const std::string& towerType);
	bool towerTowerExisted(int row, int col);

public:
	TowerManager(sf::RenderWindow* window, BulletManager* rbulletManager);
	~TowerManager();

	// --- Các hàm Public chính ---
	void ReadFile(const std::string& filePath);
	void update(float deltaTime, std::vector<enemy*>& enemies);
	void draw(sf::RenderWindow& window);
	void handleMouseClick(sf::Vector2f worldPos, int& money);
	void reset();
};