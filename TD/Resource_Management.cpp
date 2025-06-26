#include "Resource_Management.h"

std::vector<sf::Texture> Resource_Management::Mage_Sleame;
std::vector<sf::Texture> Resource_Management::Knight_Sleame;
std::vector<sf::Texture> Resource_Management::Sleame;

void Resource_Management::loadTexture()
{
	Mage_Sleame.resize(3);
	Mage_Sleame[0].loadFromFile("Pic\\3enemy\\MageSleame\\Mage Sleame1.png");
	Mage_Sleame[1].loadFromFile("Pic\\3enemy\\MageSleame\\Mage Sleame2.png");
	Mage_Sleame[2].loadFromFile("Pic\\3enemy\\MageSleame\\Mage Sleame3.png");

	Knight_Sleame.resize(3);
	Knight_Sleame[0].loadFromFile("Pic\\3enemy\\KnightSleame\\KnightSleame1.png");
	Knight_Sleame[1].loadFromFile("Pic\\3enemy\\KnightSleame\\KnightSleame2.png");
	Knight_Sleame[2].loadFromFile("Pic\\3enemy\\KnightSleame\\KnightSleame3.png");

	Sleame.resize(3);
	Sleame[0].loadFromFile("Pic\\3enemy\\Sleame\\Sleame1.png");
	Sleame[1].loadFromFile("Pic\\3enemy\\Sleame\\Sleame2.png");
	Sleame[2].loadFromFile("Pic\\3enemy\\Sleame\\Sleame3.png");
}

//Mage_Sleame, Knight_Sleame, Sleame
std::vector<sf::Texture>& Resource_Management::getTexture(const std::string& enemy_Name) {
	static bool IsLoaded = false;//Not thread safe, will find a way to fix it later

	if (!IsLoaded) {
		loadTexture();
		IsLoaded = true;
	}

	if (enemy_Name == "Mage_Sleame") {
		return Mage_Sleame;
	}
	else if (enemy_Name == "Knight_Sleame") {
		return Knight_Sleame;
	}
	else if (enemy_Name == "Sleame") {
		return Sleame;
	}
	throw "Hinh nhu nhap sai ten";
}
