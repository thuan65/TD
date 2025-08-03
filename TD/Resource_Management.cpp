#include "Resource_Management.h"
#include <iostream>
#include <stdexcept>

// --- Định nghĩa các biến static ---
// Biến cờ
bool Resource_Management::m_isInitialized = false;

// Các vector texture
std::vector<sf::Texture> Resource_Management::Map_Game1;
std::vector<sf::Texture> Resource_Management::Map_Game2;
std::vector<sf::Texture> Resource_Management::Map_Game3;
std::vector<sf::Texture> Resource_Management::Map_Game4;
std::vector<sf::Texture> Resource_Management::Mage_Sleame;
std::vector<sf::Texture> Resource_Management::Knight_Sleame;
std::vector<sf::Texture> Resource_Management::Sleame;
std::vector<sf::Texture> Resource_Management::Tower1;
std::vector<sf::Texture> Resource_Management::Tower2;
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
// --- Định nghĩa các hàm static ---

// Hàm này sẽ được gọi một lần duy nhất từ game::game()
void Resource_Management::init() {
    // Nếu đã khởi tạo rồi thì không làm gì cả
    if (m_isInitialized) {
        return;
    }

    try {
        ///////////////////////Load Enemy Texture///////////////////////////////////////
        loadFrame(Mage_Sleame, "Data\\3enemy\\MageSleame\\Mage Sleame", 3);
        loadFrame(Knight_Sleame, "Data\\3enemy\\KnightSleame\\KnightSleame", 2);
        loadFrame(Mage_Sleame, "Data\\3enemy\\MageSleame\\Mage Sleame", 3);
        loadFrame(Sleame, "Data\\3enemy\\Sleame\\Sleame", 3);

        ///////////////////////Load Map Texture///////////////////////////////////////
        loadFrame(Map_Game1, "Data\\4map\\Texture\\Map1\\Map1_Frame", 2);
        loadFrame(Map_Game2, "Data\\4map\\Texture\\Map2\\Map2_Frame", 2);
        loadFrame(Map_Game3, "Data\\4map\\Texture\\Map3\\Map3_Frame", 2);
        loadFrame(Map_Game4, "Data\\4map\\Texture\\Map4\\Map4_Frame", 2);

        ///////////////////////Load Tower Texture///////////////////////////////////////
        loadFrame(Tower1, "Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame", 2);
        loadFrame(Tower2, "Data\\2tower\\Tower\\IceTower\\IceTowerFrame", 2);
        loadFrame(Tower3, "Data\\2tower\\Tower\\ElectricTower\\ElectricTowerFrame", 2);
        loadFrame(Tower4, "Data\\2tower\\Tower\\FlameTower\\FlameTowerFrame", 2);

        ///////////////////////Load Tower Icon ///////////////////////////////////////
        loadFrame(Tower1_Icon, "Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame", 2);
        loadFrame(Tower2_Icon, "Data\\2tower\\Tower\\IceTower\\IceTowerFrame", 2);
        loadFrame(Tower3_Icon, "Data\\2tower\\Tower\\ElectricTower\\ElectricTowerFrame", 2);
        loadFrame(Tower4_Icon, "Data\\2tower\\Tower\\FlameTower\\FlameTowerFrame", 2);

        bullet1.resize(1);
        if (!bullet1[0].loadFromFile("Data\\5bullet\\test.png"))
            throw std::runtime_error("Failed to load bullet texture");

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

void Resource_Management::loadFrame(std::vector<sf::Texture>& textures, const std::string& filePath, int size) {
    textures.reserve(size);
    std::string baseName;
    size_t pos = filePath.find_last_of("\\/");
    if (pos != std::string::npos) {
        baseName = filePath.substr(pos + 1);
    }
    else {
        baseName = filePath;//TH khong co dau
    }

    for (int i = 0; i < size; ++i) {
        sf::Texture texture;
        if (texture.loadFromFile(filePath + std::to_string(i + 1) + ".png") == false) {
            throw std::invalid_argument("Erorr loading" + baseName + "frame!");
        }
        textures.push_back(texture);
    }
}

const std::vector<sf::Texture>& Resource_Management::getTexture(const std::string& name) {
    if (!m_isInitialized) {
        // Đây là một chốt an toàn, nhưng tốt nhất là nên gọi init() một cách tường minh
        init();
    }

    if (name == "Mage_Sleame") return Mage_Sleame;
    if (name == "Knight_Sleame") return Knight_Sleame;
    if (name == "Sleame") return Sleame;
    if (name == "Map_Game1") return Map_Game1;
    if (name == "Map_Game2") return Map_Game2;
    if (name == "Map_Game3") return Map_Game3;
    if (name == "Map_Game4") return Map_Game4;
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