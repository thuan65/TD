#pragma once
#include <vector>
#include <String>
#include <SFML/Graphics.hpp>

class Resource_Management {
	Resource_Management() {};
private: 
	/////////////Map_Game_Texture////////////
	static std::vector<sf::Texture> Map_Game1;
	/*static std::vector<sf::Texture> Map_Game2;
	static std::vector<sf::Texture> Map_Game3;
	static std::vector<sf::Texture> Map_Game4;*/

	////////////Enemy_Texture/////////////////
	static std::vector<sf::Texture> Mage_Sleame;
	static std::vector<sf::Texture> Knight_Sleame;
	static std::vector<sf::Texture> Sleame;

	////////////Tower_Texture/////////////////
	static std::vector<sf::Texture> Tower1;

public:
	//load Texture
	static void loadTexture();

	//Mage_Sleame, Knight_Sleame, Sleame, Map_Game1
	static std::vector<sf::Texture>& getTexture(const std::string &);

};

