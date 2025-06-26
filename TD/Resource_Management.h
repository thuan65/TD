#pragma once
#include <vector>
#include <String>
#include <SFML/Graphics.hpp>

class Resource_Management {
	Resource_Management() {};
private: 
	/////////////Map_Texture////////////
	/*static std::vector<sf::Texture> map1;*/
	/*static std::vector<sf::Texture> map2;
	static std::vector<sf::Texture> map3;
	static std::vector<sf::Texture> map4;*/

	////////////Enemt_Texture/////////////////
	static std::vector<sf::Texture> Mage_Sleame;
	static std::vector<sf::Texture> Knight_Sleame;
	static std::vector<sf::Texture> Sleame;

public:
	//load Texture
	static void loadTexture();

	//Mage_Sleame, Knight_Sleame, Sleame
	static std::vector<sf::Texture>& getTexture(const std::string &);

};

