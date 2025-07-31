#include "Resource_Management.h"
#include <iostream>

std::vector<sf::Texture> Resource_Management::Map_Game1;
//std::vector<sf::Texture> Resource_Management::Map_Game2;
//std::vector<sf::Texture> Resource_Management::Map_Game3;
//std::vector<sf::Texture> Resource_Management::Map_Game4;
std::vector<sf::Texture> Resource_Management::Mage_Sleame;
std::vector<sf::Texture> Resource_Management::Knight_Sleame;
std::vector<sf::Texture> Resource_Management::Sleame;

std::vector<sf::Texture> Resource_Management::Tower1;


std::vector<sf::Texture> Resource_Management::bullet1;


std::vector<sf::Texture> Resource_Management::loadFrame(const std::string& filePath, int count) {
	std::vector<sf::Texture> textures;

	textures.reserve(count);
	for (int i = 0; i < count; ++i) {
		sf::Texture texture;
		if (texture.loadFromFile(filePath + std::to_string(i + 1) + ".png") == false) {
			throw std::invalid_argument("Erorr loading Enemy frame!");

		}
		textures.push_back(std::move(texture));
	}

	return textures;
}

void Resource_Management::loadTexture()
{

	Mage_Sleame = loadFrame("Data\\3enemy\\MageSleame\\Mage Sleame", 3);//RVO or Move semantics

	Knight_Sleame = loadFrame("Data\\3enemy\\KnightSleame\\KnightSleame", 3);

	Sleame = loadFrame("Data\\3enemy\\Sleame\\Sleame", 3);

	Map_Game1 = loadFrame("Data\\4map\\Texture\\map1\\map1_Frame", 2);

	Tower1 = loadFrame("Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame", 2);


	bullet1.resize(1);
	bullet1[0].loadFromFile("Data\\5bullet\\test.png");

}

//Mage_Sleame, Knight_Sleame, Sleame, Map_Game1
std::vector<sf::Texture>& Resource_Management::getTexture(const std::string& Texture_Name) {

	if (Texture_Name == "Mage_Sleame") {
		return Mage_Sleame;
	}
	else if (Texture_Name == "Knight_Sleame") {
		return Knight_Sleame;
	}
	else if (Texture_Name == "Sleame") {
		return Sleame;
	}
	else if (Texture_Name == "Map_Game1") {
		return Map_Game1;
	}
	else if (Texture_Name == "Tower1") {
		return Tower1;
	}
	else if (Texture_Name == "bullet") {
		return bullet1;
	}

	throw "Hinh nhu nhap sai ten";
}
