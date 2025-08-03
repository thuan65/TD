#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Resource_Management {
private:
	// Constructor private để không ai tạo đối tượng được
	Resource_Management() = default;

	// Các biến texture vẫn là static private
	static std::vector<sf::Texture> Map_Game1;
	static std::vector<sf::Texture> Mage_Sleame;
	static std::vector<sf::Texture> Knight_Sleame;
	static std::vector<sf::Texture> Sleame;
	static std::vector<sf::Texture> Tower1;
	static std::vector<sf::Texture> Tower2;
	static std::vector<sf::Texture> Tower3;
	static std::vector<sf::Texture> Tower4;
	static std::vector<sf::Texture> bullet1;
	static std::vector<sf::Texture> Tower1_Icon;
	static std::vector<sf::Texture> Tower2_Icon;
	static std::vector<sf::Texture> Tower3_Icon;
	static std::vector<sf::Texture> Tower4_Icon;
	static std::vector<sf::Texture> Heart_Icon;
	static std::vector<sf::Texture> Victory_Image;
	static std::vector<sf::Texture> GameOver_Image;


public:
	// Các hàm là public static
	static void init(); // Đổi tên loadTexture thành init cho rõ ràng
	static const std::vector<sf::Texture>& getTexture(const std::string& name);
	static std::vector<std::vector<sf::Texture>> Digits;

private:
	// Biến cờ để đảm bảo chỉ load 1 lần
	static bool m_isInitialized;
};
