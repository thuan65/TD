#include "Resource_Management.h"

std::vector<sf::Texture> Resource_Management::Map_Game1;
//std::vector<sf::Texture> Resource_Management::Map_Game2;
//std::vector<sf::Texture> Resource_Management::Map_Game3;
//std::vector<sf::Texture> Resource_Management::Map_Game4;
std::vector<sf::Texture> Resource_Management::Mage_Sleame;
std::vector<sf::Texture> Resource_Management::Knight_Sleame;
std::vector<sf::Texture> Resource_Management::Sleame;

std::vector<sf::Texture> Resource_Management::Tower1;

void Resource_Management::loadTexture()
{
	Mage_Sleame.resize(3);
	for (int i = 0; i < 3; ++i) {
		sf::Texture mageSleameTexture;
		if (mageSleameTexture.loadFromFile("Data\\3enemy\\MageSleame\\Mage Sleame" + std::to_string(i + 1) + ".png") == false) {
			throw std::invalid_argument("Erorr loading Enemy frame!");

		}
		Mage_Sleame[i] = std::move(mageSleameTexture);
	}

	Knight_Sleame.resize(3);
	for (int i = 0; i < 3; ++i) {
		sf::Texture knight_SleameTexture;
		if (knight_SleameTexture.loadFromFile("Data\\3enemy\\MageSleame\\Mage Sleame" + std::to_string(i + 1) + ".png") == false) {
			throw std::invalid_argument("Erorr loading Enemy frame!");

		}
		Knight_Sleame[i] = std::move(knight_SleameTexture);
	}

	Sleame.resize(3);
	for (int i = 0; i < 3; ++i) {
		sf::Texture sleameTexture;
		if (sleameTexture.loadFromFile("Data\\3enemy\\MageSleame\\Mage Sleame" + std::to_string(i + 1) + ".png") == false) {
			throw std::invalid_argument("Erorr loading Enemy frame!");

		}
		Sleame[i] = std::move(sleameTexture);
	}

	Map_Game1.resize(2);
	for (int i = 0; i < 2; ++i) {
		sf::Texture tmpMap_GameTexture;
		if (tmpMap_GameTexture.loadFromFile("Data\\4map\\Texture\\map1\\map1_Frame" + std::to_string(i) + ".png") == false) {
			throw std::invalid_argument("Erorr loading Map_Game frame!");
		
		}
		Map_Game1[i] = std::move(tmpMap_GameTexture);
	}

	Tower1.resize(1);
	for (int i = 0; i < 1; ++i) {
		sf::Texture tower1Texture;
		if (tower1Texture.loadFromFile("Data\\2tower\\tempTowerObject.png") == false) {
			throw std::invalid_argument("Erorr loading Map_Game frame!");

		}
		Tower1[i] = std::move(tower1Texture);
	}

}

//Mage_Sleame, Knight_Sleame, Sleame, Map_Game1
std::vector<sf::Texture>& Resource_Management::getTexture(const std::string& Texture_Name) {
	static bool IsLoaded = false;//Not thread safe, will find a way to fix it later

	if (!IsLoaded) {
		loadTexture();
		IsLoaded = true;
	}

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

	throw "Hinh nhu nhap sai ten";
}
