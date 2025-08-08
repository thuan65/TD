#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Resource_Management {
private:
	// Constructor private để không ai tạo đối tượng được
	Resource_Management() = default;

	



	// Các biến texture vẫn là static private
	
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
	static std::vector<sf::Texture> Upgrade_Icon;
	static std::vector<sf::Texture> Sell_Icon;


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

	///////////////////Mage_Sleame///////////////////
	static std::vector<sf::Texture> Mage_Sleame_Movement;
	static std::vector<sf::Texture> Mage_Sleame_Hurt;
	//static std::vector<sf::Texture> Mage_Sleame_Dead;
	///////////////////Texture của các con enemy/////


public:
	// Các hàm là public static
	static void init(); // Đổi tên loadTexture thành init cho rõ ràng
	static const std::vector<sf::Texture>& getTexture(const std::string& name);
	static std::vector<std::vector<sf::Texture>> Digits;
	static void loadFrame(std::vector<sf::Texture>& textures, const std::string& filePath, int size);
	static void loadFrame(std::vector<sf::Texture>& textures, const std::string& filePath, const std::string& baseName, int size);

	static sf::Font arialFont;
	static sf::Texture mainMenuBackgroundTexture;
	static sf::Texture mapSelectBackgroundTexture;

	static std::vector<sf::Texture> Map_Game1;
	static std::vector<sf::Texture> Map_Game2;
	static std::vector<sf::Texture> Map_Game3;
	static std::vector<sf::Texture> Map_Game4;

	//Remove thoose thing later/////////////////////////////
	static std::vector<sf::Texture> Map1BackgroundTexture;
	static std::vector<sf::Texture> Map2BackgroundTexture;
	static std::vector<sf::Texture> Map3BackgroundTexture;
	static std::vector<sf::Texture> Map4BackgroundTexture;
	//Remove thoose thing later/////////////////////////////

	static sf::Texture arrowTexture;
	static sf::Texture pauseIconTexture;
	static sf::Texture victoryBackgroundTexture;
	static sf::Texture loseBackgroundTexture;

private:
	// Biến cờ để đảm bảo chỉ load 1 lần
	static bool m_isInitialized;

	static void loadTexture(sf::Texture& texture, const std::string& filepath);//Load only one Texture
	static void loadFont(sf::Font& font, const std::string& filepath);

public:
	static const unsigned int WINDOW_WIDTH;
	static const unsigned int WINDOW_HEIGHT;

	static sf::Color buttonShapeFillColor; // grey
	static sf::Color colorWhenClickOnButton; // soft bluish-purple

};
