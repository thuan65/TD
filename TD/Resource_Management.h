#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Resource_Management {
<<<<<<< HEAD
<<<<<<< HEAD
private:
	// Constructor private để không ai tạo đối tượng được
	Resource_Management() = default;
=======
=======
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24
	Resource_Management() { loadTexture(); };
private: 
	//Prevent copy
	Resource_Management(const Resource_Management&) = delete;
	Resource_Management& operator= (const Resource_Management&) = delete;

	/////////////Map_Game_Texture////////////
	static std::vector<sf::Texture> Map_Game1;
	/*static std::vector<sf::Texture> Map_Game2;
	static std::vector<sf::Texture> Map_Game3;
	static std::vector<sf::Texture> Map_Game4;*/
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24

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
<<<<<<< HEAD
	// Các hàm là public static
	static void init(); // Đổi tên loadTexture thành init cho rõ ràng
	static const std::vector<sf::Texture>& getTexture(const std::string& name);
	static std::vector<std::vector<sf::Texture>> Digits;
=======
	//load Texture
	static void loadTexture();
	static std::vector<sf::Texture> loadFrame(const std::string& filePath, int count);

	//Mage_Sleame, Knight_Sleame, Sleame, Map_Game1
	static std::vector<sf::Texture>& getTexture(const std::string &);
	
	static Resource_Management& getInstance() {
		static Resource_Management instance;
		return instance;
	}


};
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24

private:
	// Biến cờ để đảm bảo chỉ load 1 lần
	static bool m_isInitialized;
};