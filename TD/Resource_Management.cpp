<<<<<<< HEAD
﻿#include "Resource_Management.h"
#include <iostream>
#include <stdexcept>
=======
#include "Resource_Management.h"
#include <iostream>
<<<<<<< HEAD
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24
=======
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24

// --- Định nghĩa các biến static ---
// Biến cờ
bool Resource_Management::m_isInitialized = false;

// Các vector texture
std::vector<sf::Texture> Resource_Management::Map_Game1;
std::vector<sf::Texture> Resource_Management::Mage_Sleame;
std::vector<sf::Texture> Resource_Management::Knight_Sleame;
std::vector<sf::Texture> Resource_Management::Sleame;
std::vector<sf::Texture> Resource_Management::Tower1;
<<<<<<< HEAD
std::vector<sf::Texture> Resource_Management::Tower2;
=======


<<<<<<< HEAD
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24
=======
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24
std::vector<sf::Texture> Resource_Management::bullet1;
std::vector<sf::Texture> Resource_Management::Tower1_Icon;
std::vector<sf::Texture> Resource_Management::Tower2_Icon;
std::vector<sf::Texture> Resource_Management::Tower3;
std::vector<sf::Texture> Resource_Management::Tower4;
std::vector<sf::Texture> Resource_Management::Tower3_Icon;
std::vector<sf::Texture> Resource_Management::Tower4_Icon;
std::vector<sf::Texture> Resource_Management::Heart_Icon;
std::vector<std::vector<sf::Texture>> Resource_Management::Digits;
std::vector<sf::Texture> Resource_Management::Victory_Image;
std::vector<sf::Texture> Resource_Management::GameOver_Image;


<<<<<<< HEAD
// --- Định nghĩa các hàm static ---

// Hàm này sẽ được gọi một lần duy nhất từ game::game()
void Resource_Management::init()
{
    // Nếu đã khởi tạo rồi thì không làm gì cả
    if (m_isInitialized) {
        return;
    }

    try {
        Mage_Sleame.resize(3);
        for (int i = 0; i < 3; ++i) {
            if (!Mage_Sleame[i].loadFromFile("Data\\3enemy\\MageSleame\\Mage Sleame" + std::to_string(i + 1) + ".png"))
                throw std::runtime_error("Failed to load Mage Sleame texture");
        }

        Knight_Sleame.resize(3);
        for (int i = 0; i < 3; ++i) {
            if (!Knight_Sleame[i].loadFromFile("Data\\3enemy\\KnightSleame\\KnightSleame" + std::to_string(i + 1) + ".png"))
                throw std::runtime_error("Failed to load Knight Sleame texture");
        }

        Sleame.resize(3);
        for (int i = 0; i < 3; ++i) {
            if (!Sleame[i].loadFromFile("Data\\3enemy\\Sleame\\Sleame" + std::to_string(i + 1) + ".png"))
                throw std::runtime_error("Failed to load Sleame texture");
        }

        Map_Game1.resize(2);
        for (int i = 0; i < 2; ++i) {
            if (!Map_Game1[i].loadFromFile("Data\\4map\\Texture\\map1\\map1_Frame" + std::to_string(i) + ".png"))
                throw std::runtime_error("Failed to load map texture");
        }

        Tower1.resize(1);
        if (!Tower1[0].loadFromFile("Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower1 texture");

        Tower2.resize(1);
        // !!! THAY ĐỔI ĐƯỜNG DẪN NÀY !!!
        if (!Tower2[0].loadFromFile("Data\\2tower\\Tower\\IceTower\\IceTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower2 texture");

        Tower3.resize(1);
        if (!Tower3[0].loadFromFile("Data\\2tower\\Tower\\ElectricTower\\ElectricTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower3 texture");


        Tower4.resize(1);
        if (!Tower4[0].loadFromFile("Data\\2tower\\Tower\\FlameTower\\FlameTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower4 texture");
=======
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
<<<<<<< HEAD
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24
=======
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24

        bullet1.resize(1);
        if (!bullet1[0].loadFromFile("Data\\5bullet\\test.png"))
            throw std::runtime_error("Failed to load bullet texture");

        Tower1_Icon.resize(1);
        // !!! THAY ĐỔI ĐƯỜNG DẪN NÀY !!!
        if (!Tower1_Icon[0].loadFromFile("Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower1_Icon");

        Tower2_Icon.resize(1);
        // !!! THAY ĐỔI ĐƯỜNG DẪN NÀY !!!
        if (!Tower2_Icon[0].loadFromFile("Data\\2tower\\Tower\\IceTower\\IceTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower2_Icon");


        Tower3_Icon.resize(1);
        // !!! THAY ĐỔI ĐƯỜNG DẪN NÀY !!!
        if (!Tower3_Icon[0].loadFromFile("Data\\2tower\\Tower\\ElectricTower\\ElectricTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower3_Icon");



        Tower4_Icon.resize(1);
        // !!! THAY ĐỔI ĐƯỜNG DẪN NÀY !!!
        if (!Tower4_Icon[0].loadFromFile("Data\\2tower\\Tower\\FlameTower\\FlameTowerFrame0.png"))
            throw std::runtime_error("Failed to load Tower4_Icon");

        Heart_Icon.resize(1);
        if (!Heart_Icon[0].loadFromFile("Data/GUI/heart.png"))
            throw std::runtime_error("Failed to load Heart_Icon");

        Digits.resize(10); // Có 10 chữ số từ 0 đến 9
        for (int i = 0; i < 10; ++i) {
            Digits[i].resize(1);
            if (!Digits[i][0].loadFromFile("Data/GUI/number_" + std::to_string(i) + ".png"))
                throw std::runtime_error("Failed to load digit " + std::to_string(i));
        }
        Victory_Image.resize(1);
        if (!Victory_Image[0].loadFromFile("Data/GUI/victory.png"))
            throw std::runtime_error("Failed to load Victory_Image");

        GameOver_Image.resize(1);
        if (!GameOver_Image[0].loadFromFile("Data/GUI/game_over.png"))
            throw std::runtime_error("Failed to load GameOver_Image");
        // Đánh dấu đã khởi tạo thành công
        m_isInitialized = true;
    }
    catch (const std::runtime_error& e) {
        // In lỗi ra console và ném lại để chương trình có thể dừng lại
        std::cerr << "Resource loading failed: " << e.what() << std::endl;
        throw;
    }
}

<<<<<<< HEAD
const std::vector<sf::Texture>& Resource_Management::getTexture(const std::string& name) {
    if (!m_isInitialized) {
        // Đây là một chốt an toàn, nhưng tốt nhất là nên gọi init() một cách tường minh
        init();
    }

    if (name == "Mage_Sleame") return Mage_Sleame;
    if (name == "Knight_Sleame") return Knight_Sleame;
    if (name == "Sleame") return Sleame;
    if (name == "Map_Game1") return Map_Game1;
    if (name == "Tower1") return Tower1;
    if (name == "Tower2") return Tower2;
    if (name == "Tower3") return Tower3;
    if (name == "Tower4") return Tower4;
    if (name == "bullet") return bullet1;
    if (name == "Tower1_Icon") return Tower1_Icon;
    if (name == "Tower2_Icon") return Tower2_Icon;
    if (name == "Tower3_Icon") return Tower3_Icon;
    if (name == "Tower4_Icon") return Tower4_Icon;
    if (name == "Heart_Icon") return Heart_Icon;
    if (name == "Victory_Image") return Victory_Image;
    if (name == "GameOver_Image") return GameOver_Image;

    // Nếu không tìm thấy, ném một ngoại lệ rõ ràng
    throw std::runtime_error("Texture not found: " + name);
}
=======
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
>>>>>>> dee9fe8d4c05a8b1d6faece8c4a30abc9df92a24
