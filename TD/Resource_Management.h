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
	static std::vector<sf::Texture> Map_Game2;
	static std::vector<sf::Texture> Map_Game3;
	static std::vector<sf::Texture> Map_Game4;
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


///////////////////Texture của các con enemy///////////////////
	///////////////////Dumber///////////////////
	static std::vector<sf::Texture> Dumber_Movement;
	static std::vector<sf::Texture> Dumber_Hurt;
	static std::vector<sf::Texture> Dumber_Dead;
	///////////////////Dumber///////////////////

	///////////////////Ghast///////////////////
	static std::vector<sf::Texture> Ghast_Movement;
	static std::vector<sf::Texture> Ghast_Hurt;
	static std::vector<sf::Texture> Ghast_Dead;
	///////////////////Ghast///////////////////

	///////////////////Nightmare///////////////////
	static std::vector<sf::Texture> Nightmare_Movement;
	static std::vector<sf::Texture> Nightmare_Hurt;
	static std::vector<sf::Texture> Nightmare_Dead;
	///////////////////Nightmare///////////////////

	///////////////////Runner///////////////////
	static std::vector<sf::Texture> Runner_Movement;
	static std::vector<sf::Texture> Runner_Hurt;
	static std::vector<sf::Texture> Runner_Dead;
	///////////////////Runner///////////////////

///////////////////Texture của các con enemy///////////////////


public:
	// Các hàm là public static
	static void init(); // Đổi tên loadTexture thành init cho rõ ràng
	static const std::vector<sf::Texture>& getTexture(const std::string& name);
	static std::vector<std::vector<sf::Texture>> Digits;
	static void loadFrame(std::vector<sf::Texture>& textures, const std::string& filePath, int size);
	static void loadFrame(std::vector<sf::Texture>& textures, const std::string& filePath, const std::string& baseName, int size);

private:
	// Biến cờ để đảm bảo chỉ load 1 lần
	static bool m_isInitialized;
};
