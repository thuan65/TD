#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Resource_Management {
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

	////////////Enemy_Texture/////////////////
	static std::vector<sf::Texture> Mage_Sleame;
	static std::vector<sf::Texture> Knight_Sleame;
	static std::vector<sf::Texture> Sleame;

	////////////Tower_Texture/////////////////
	static std::vector<sf::Texture> Tower1;


	////////////Bullet_Texture/////////////////
	static std::vector<sf::Texture> bullet1;

public:
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

