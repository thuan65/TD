#include "Resource_Management.h"
#include <iostream>
#include <stdexcept>

// --- Định nghĩa các biến static ---
// Biến cờ
bool Resource_Management::m_isInitialized = false;

sf::Font Resource_Management::arialFont;
sf::Texture Resource_Management::mainMenuBackgroundTexture;
sf::Texture Resource_Management::mapSelectBackgroundTexture;
std::vector<sf::Texture> Resource_Management::Map1BackgroundTexture(2);
std::vector<sf::Texture> Resource_Management::Map2BackgroundTexture(2);
std::vector<sf::Texture> Resource_Management::Map3BackgroundTexture(2);
std::vector<sf::Texture> Resource_Management::Map4BackgroundTexture(2);
sf::Texture Resource_Management::arrowTexture;
sf::Texture Resource_Management::pauseIconTexture;
sf::Texture Resource_Management::victoryBackgroundTexture;
sf::Texture Resource_Management::loseBackgroundTexture;

// Các vector texture
std::vector<sf::Texture> Resource_Management::Map_Game1;
std::vector<sf::Texture> Resource_Management::Map_Game2;
std::vector<sf::Texture> Resource_Management::Map_Game3;
std::vector<sf::Texture> Resource_Management::Map_Game4;
std::vector<sf::Texture> Resource_Management::FreezeTower;
std::vector<sf::Texture> Resource_Management::DarkTower;
std::vector<sf::Texture> Resource_Management::bullet1;
std::vector<sf::Texture> Resource_Management::bullet2;
std::vector<sf::Texture> Resource_Management::bullet3;
std::vector<sf::Texture> Resource_Management::bullet4;

std::vector<sf::Texture> Resource_Management::Tower1_Icon;
std::vector<sf::Texture> Resource_Management::Tower2_Icon;
std::vector<sf::Texture> Resource_Management::ElectricTower;
std::vector<sf::Texture> Resource_Management::FlameTower;
std::vector<sf::Texture> Resource_Management::Tower3_Icon;
std::vector<sf::Texture> Resource_Management::Tower4_Icon;
std::vector<sf::Texture> Resource_Management::Tower1_L2;
std::vector<sf::Texture> Resource_Management::Tower2_L2;
std::vector<sf::Texture> Resource_Management::Tower3_L2;
std::vector<sf::Texture> Resource_Management::Tower4_L2;

sf::Texture Resource_Management::Heart_Icon;
std::vector<std::vector<sf::Texture>> Resource_Management::Digits;
std::vector<sf::Texture> Resource_Management::Victory_Image;
std::vector<sf::Texture> Resource_Management::GameOver_Image;
std::vector<sf::Texture> Resource_Management::Knight_Sleame;
std::vector<sf::Texture> Resource_Management::Knight_Sleame_Hurt;
std::vector<sf::Texture> Resource_Management::Knight_Sleame_Dead;
std::vector<sf::Texture> Resource_Management::Sleame;
std::vector<sf::Texture> Resource_Management::Sleame_Hurt;
std::vector<sf::Texture> Resource_Management::Sleame_Dead;
std::vector<sf::Texture> Resource_Management::Dumber_Movement;
std::vector<sf::Texture> Resource_Management::Dumber_Hurt;
std::vector<sf::Texture> Resource_Management::Dumber_Dead;
std::vector<sf::Texture> Resource_Management::Ghast_Movement;
std::vector<sf::Texture> Resource_Management::Ghast_Hurt;
std::vector<sf::Texture> Resource_Management::Ghast_Dead;
std::vector<sf::Texture> Resource_Management::Nightmare_Movement;
std::vector<sf::Texture> Resource_Management::Nightmare_Hurt;
std::vector<sf::Texture> Resource_Management::Nightmare_Dead;
std::vector<sf::Texture> Resource_Management::Runner_Movement;
std::vector<sf::Texture> Resource_Management::Runner_Hurt;
std::vector<sf::Texture> Resource_Management::Runner_Dead;
std::vector<sf::Texture> Resource_Management::Mushroom;
std::vector<sf::Texture> Resource_Management::Mushroom_Hurt;
std::vector<sf::Texture> Resource_Management::Mushroom_Dead;
std::vector<sf::Texture> Resource_Management::Fly;
std::vector<sf::Texture> Resource_Management::Fly_Hurt;
std::vector<sf::Texture> Resource_Management::Fly_Dead;

std::vector<sf::Texture> Resource_Management::Mage_Sleame_Movement;
std::vector<sf::Texture> Resource_Management::Mage_Sleame_Hurt;
std::vector<sf::Texture> Resource_Management::Mage_Sleame_Dead;
std::vector<sf::Texture> Resource_Management::Upgrade_Icon;
std::vector<sf::Texture> Resource_Management::Sell_Icon;

std::vector<sf::Texture> Resource_Management::NoTexture;


sf::Texture Resource_Management::loadGameBackgroundTexture;

sf::SoundBuffer Resource_Management::buttonClickSound;
sf::SoundBuffer Resource_Management::buttonClickErrorSound;
sf::SoundBuffer Resource_Management::boomSound;

sf::Font Resource_Management::font;
std::vector<sf::Texture> Resource_Management::loadingFrameTexture;
sf::Texture Resource_Management::leftArrowTexture;
sf::Texture Resource_Management::speedUpIconTexture;
sf::Texture Resource_Management::playIconTexture;


sf::Texture Resource_Management::mainMenuButtonTexture;
sf::Texture Resource_Management::newGameButtonTexture;
sf::Texture Resource_Management::loadGameButtonTexture;
sf::Texture Resource_Management::settingButtonTexture;
sf::Texture Resource_Management::quitButtonTexture;
sf::Texture Resource_Management::continueGameButtonTexture;
sf::Texture Resource_Management::saveGameButtonTexture;
sf::Texture Resource_Management::barVolumeTexture;
sf::Texture Resource_Management::knobVolumeTexture;
sf::Texture Resource_Management::yesIconTexture;
sf::Texture Resource_Management::noIconTexture;






// --- Định nghĩa các hàm static ---

// Hàm này sẽ được gọi một lần duy nhất từ game::game()
void Resource_Management::init() {
    // Nếu đã khởi tạo rồi thì không làm gì cả
    if (m_isInitialized) {
        return;
    }

    try {
        ///////////////////////No Texture template///////////////////////////////////////
        loadFrame(NoTexture, "Data\\2tower\\tempTowerObject", 1);

        ///////////////////////Load Enemy Texture///////////////////////////////////////
        loadFrame(Knight_Sleame, "Data\\3enemy\\KnightSleame\\KnightSleame", 2);
    ;
        loadFrame(Sleame, "Data\\3enemy\\Sleame\\Sleame", 3);

        ///////////////////////Load Map Texture///////////////////////////////////////
        loadFrame(Map_Game1, "Data\\4map\\Texture\\Map1\\Map1_Frame", 2);
        loadFrame(Map_Game2, "Data\\4map\\Texture\\Map2\\Map2_Frame", 2);
        loadFrame(Map_Game3, "Data\\4map\\Texture\\Map3\\Map3_Frame", 2);
        loadFrame(Map_Game4, "Data\\4map\\Texture\\Map4\\Map4_Frame", 2);

        ///////////////////////Load Tower Texture///////////////////////////////////////
        loadFrame(DarkTower, "Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame", 2);
        loadFrame(FreezeTower, "Data\\2tower\\Tower\\IceTower\\IceTowerFrame", 2);
        loadFrame(ElectricTower, "Data\\2tower\\Tower\\ElectricTower\\ElectricTowerFrame", 2);
        loadFrame(FlameTower, "Data\\2tower\\Tower\\FlameTower\\FlameTowerFrame", 2);

        ///////////////////////Load Tower Icon ///////////////////////////////////////
        loadFrame(Tower1_Icon, "Data\\2tower\\Tower\\DarkTower\\DarkTowerFrame", 2);
        loadFrame(Tower2_Icon, "Data\\2tower\\Tower\\IceTower\\IceTowerFrame", 2);
        loadFrame(Tower3_Icon, "Data\\2tower\\Tower\\ElectricTower\\ElectricTowerFrame", 2);
        loadFrame(Tower4_Icon, "Data\\2tower\\Tower\\FlameTower\\FlameTowerFrame", 2);

        loadFrame(Tower1_L2, "Data\\2tower\\Tower_2\\DarkTower\\DarkTowerFrame", 2);
        loadFrame(Tower2_L2, "Data\\2tower\\Tower_2\\IceTower\\IceTowerFrame", 2);
        loadFrame(Tower3_L2, "Data\\2tower\\Tower_2\\ElectricTower\\ElectricTowerFrame", 2);
        loadFrame(Tower4_L2, "Data\\2tower\\Tower_2\\FlameTower\\FlameTowerFrame", 2);
        
        ///////////////////////Load Enemy Texture ///////////////////////////////////////
        loadFrame(Dumber_Movement, "Data\\3enemy\\Dumber\\Movement\\DumperMovement_Frame", 4);
        loadFrame(Dumber_Hurt, "Data\\3enemy\\Dumber\\Hurt\\DumperHurt_Frame", 4);
        loadFrame(Dumber_Dead, "Data\\3enemy\\Dumber\\Dead\\Dumper Dead Frame ", 4);

        loadFrame(Ghast_Movement, "Data\\3enemy\\Ghast\\Movement\\Ghast Movement Frame ", 4);
        loadFrame(Ghast_Hurt, "Data\\3enemy\\Ghast\\Hurt\\Ghast Hurt Frame ", 4);
        loadFrame(Ghast_Dead, "Data\\3enemy\\Ghast\\Dead\\Ghast Dead Frame ", 4);

        loadFrame(Nightmare_Movement, "Data\\3enemy\\Nightmare\\Nightmare Movement\\Nightmare Movement Frame ", 4);
        loadFrame(Nightmare_Hurt, "Data\\3enemy\\Nightmare\\Nightmare Hurt\\Nightmare Hurt Frame ", 4);
        loadFrame(Nightmare_Dead, "Data\\3enemy\\Nightmare\\Nightmare Dead\\Nightmare Dead Frame ", 4);

        loadFrame(Runner_Movement, "Data\\3enemy\\Runner\\Movement\\Runner Movement Frame ", 4);
        loadFrame(Runner_Hurt, "Data\\3enemy\\Runner\\Hurt\\Runner Hurt Frame ", 4);
        loadFrame(Runner_Dead, "Data\\3enemy\\Runner\\Dead\\Runner Dead Frame ", 4);

        loadFrame(Mushroom, "Data\\3enemy\\Mushroom\\Movement\\mushroom_", 8);
        loadFrame(Mushroom_Hurt, "Data\\3enemy\\Mushroom\\Hurt\\mushroom_hit_", 5);
        loadFrame(Mushroom_Dead, "Data\\3enemy\\Mushroom\\Dead\\mushroom_die_", 9);

        loadFrame(Fly, "Data\\3enemy\\Fly\\Movement\\enemy3_fly_", 8);
        loadFrame(Fly_Hurt, "Data\\3enemy\\Fly\\Hurt\\enemy3_hit_", 4);
        loadFrame(Fly_Dead, "Data\\3enemy\\Fly\\Dead\\enemy3_die_", 16);

        loadFrame(Mage_Sleame_Movement, "Data\\3enemy\\MageSleame\\Mage_Sleame Movement\\Mage Sleame_Movement", 3);
        loadFrame(Mage_Sleame_Hurt, "Data\\3enemy\\MageSleame\\Mage_Sleame Hurt\\MageSleame Hurt", 3);
        loadFont(arialFont, "Data\\GUI\\fonts\\arial.ttf");
        loadFont(font, "Data\\GUI\\fonts\\arcadepix.ttf");
        loadTexture(mainMenuBackgroundTexture, "Data/GUI/background/mainmenu.png");
        loadTexture(mapSelectBackgroundTexture, "Data/GUI/background/mainmenu.png");
        loadTexture(arrowTexture, "Data\\GUI\\mapselect\\arrow.png");

        loadFrame(loadingFrameTexture, "Data\\GUI\\loading\\loading_frame",5);
        loadTexture(leftArrowTexture, "Data/GUI/icon/left_arrow.png");
        loadTexture(pauseIconTexture, "Data/GUI/icon/pause.png");
        loadTexture(speedUpIconTexture, "Data/GUI/icon/speed_up.png");
        loadTexture(playIconTexture, "Data/GUI/icon/play.png");

        loadTexture(loadGameBackgroundTexture, "Data\\GUI\\background\\setting.png");

        loadTexture(mainMenuButtonTexture, "Data/GUI/button/mainmenu.png");
        loadTexture(newGameButtonTexture, "Data/GUI/button/new_game.png");
        loadTexture(loadGameButtonTexture, "Data/GUI/button/load.png");
        loadTexture(settingButtonTexture, "Data/GUI/button/setting.png");
        loadTexture(quitButtonTexture, "Data/GUI/button/quit.png");
        loadTexture(continueGameButtonTexture, "Data/GUI/button/continue.png");
        loadTexture(saveGameButtonTexture, "Data/GUI/button/save.png");

        loadTexture(barVolumeTexture, "Data/GUI/slider/volume_bar.png");
        loadTexture(knobVolumeTexture, "Data/GUI/slider/volume_knob.png");

        loadTexture(yesIconTexture, "Data/GUI/icon/yes.png");
        loadTexture(noIconTexture, "Data/GUI/icon/no.png");

        loadTexture(victoryBackgroundTexture, "Data\\GUI\\victory\\background.png");
        loadTexture(loseBackgroundTexture, "Data\\GUI\\lose\\background.png");
        loadTexture(loadGameBackgroundTexture, "Data/GUI/mapselect/background.png");

        loadTexture(Heart_Icon, "Data/GUI/heart.png");

        loadSound(buttonClickSound, "Data/audio/sound/button_click_sound.wav");
        loadSound(buttonClickErrorSound, "Data/audio/sound/button_click_error_sound.wav");
        loadSound(boomSound, "Data/audio/sound/boom_sound.wav");

        loadFrame(bullet1, "Data\\5bullet\\IceBullet", 1);
        loadFrame(bullet2, "Data\\5bullet\\DarkBullet", 1);
        loadFrame(bullet3, "Data\\5bullet\\LightningBullet", 1);
        loadFrame(bullet4, "Data\\5bullet\\FlameBullet", 1);

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

		Upgrade_Icon.resize(1);
        if (!Upgrade_Icon[0].loadFromFile("Data/GUI/UpgrateTowerButton.png"))
			throw std::runtime_error("Failed to load Upgrade_Icon");
		Sell_Icon.resize(1);
		if (!Sell_Icon[0].loadFromFile("Data/GUI/SellTowerButton.png"))
			throw std::runtime_error("Failed to load Sell_Icon");
        // Đánh dấu đã khởi tạo thành công
        m_isInitialized = true;
    }
    catch (const std::runtime_error& e) {
        // In lỗi ra console và ném lại để chương trình có thể dừng lại
        std::cerr << "Resource loading failed: " << e.what() << std::endl;
        throw;
    }

    Mage_Sleame_Dead = Mage_Sleame_Movement;
   
    Knight_Sleame_Hurt = Knight_Sleame;
    Knight_Sleame_Dead = Knight_Sleame;

    Sleame_Hurt = Sleame;
    Sleame_Dead = Sleame;
}

void Resource_Management::loadMusic(sf::Music& music, const std::string& filepath) {
    if (!music.openFromFile(filepath)) {
        std::cerr << "cannot load texture " << filepath << std::endl;
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

void Resource_Management::loadFrame(std::vector<sf::Texture>& textures, const std::string& filePath, const std::string& baseName,int size) {
    textures.reserve(size);

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

    if (name == "IceBullet") return bullet1;
    if (name == "DarkBullet") return bullet2;
    if (name == "LightningBullet") return bullet3;
    if (name == "FlameBullet") return bullet4;

    if (name == "Knight_Sleame") return Knight_Sleame;//Note the default animation is walk or movement
    if (name == "Knight_Sleame_Hurt") return Knight_Sleame_Hurt;
    if (name == "Knight_Sleame_Dead") return Knight_Sleame_Dead;

    if (name == "Sleame") return Sleame;
    if (name == "Sleame_Hurt") return Sleame_Hurt;
    if (name == "Sleame_Dead") return Sleame_Dead;

    if (name == "Dumber") return Dumber_Movement;
    if (name == "Dumber_Hurt") return Dumber_Hurt;
    if (name == "Dumber_Dead") return Dumber_Dead;

    if (name == "Ghast") return Ghast_Movement;
    if (name == "Ghast_Hurt") return Ghast_Hurt;
    if (name == "Ghast_Dead") return Ghast_Dead;
    
    if (name == "Nightmare") return Nightmare_Movement;
    if (name == "Nightmare_Hurt") return Nightmare_Hurt;
    if (name == "Nightmare_Dead") return Nightmare_Dead;

    if (name == "Runner") return Runner_Movement;
    if (name == "Runner_Hurt") return Runner_Hurt;
    if (name == "Runner_Dead") return Runner_Dead;

    if (name == "Mage_Sleame") return Mage_Sleame_Movement;
    if (name == "Mage_Sleame_Hurt") return Mage_Sleame_Hurt;
    if (name == "Mage_Sleame_Dead") return Mage_Sleame_Dead;

    if (name == "Mushroom") return Mushroom;
    if (name == "Mushroom_Hurt") return Mushroom_Hurt;
    if (name == "Mushroom_Dead") return Mushroom_Dead;

    if (name == "Fly") return Fly;
    if (name == "Fly_Hurt") return Fly_Hurt;
    if (name == "Fly_Dead") return Fly_Dead;

    if (name == "Map_Game1") return Map_Game1;
    if (name == "Map_Game2") return Map_Game2;
    if (name == "Map_Game3") return Map_Game3;
    if (name == "Map_Game4") return Map_Game4;


    if (name == "FreezeTower") return FreezeTower;
    if (name == "DarkTower") return DarkTower;
    if (name == "ElectricTower") return ElectricTower;
    if (name == "FlameTower") return FlameTower;

    if (name == "Tower1_Icon") return Tower1_Icon;
    if (name == "Tower2_Icon") return Tower2_Icon;
    if (name == "Tower3_Icon") return Tower3_Icon;
    if (name == "Tower4_Icon") return Tower4_Icon;
    //if (name == "Heart_Icon") return Heart_Icon;
    if (name == "Victory_Image") return Victory_Image;
    if (name == "GameOver_Image") return GameOver_Image;
	if (name == "Upgrade_Icon") return Upgrade_Icon;
	if (name == "Sell_Icon") return Sell_Icon;
    if (name == "DarkTower_L2") return Tower1_L2;
    if (name == "FreezeTower_L2") return Tower2_L2;
    if (name == "ElectricTower_L2") return Tower3_L2;
    if (name == "FlameTower_L2") return Tower4_L2;


    // Nếu không tìm thấy, ném một ngoại lệ rõ ràng
    throw std::runtime_error("Texture not found: " + name);
}

void Resource_Management::loadTexture(sf::Texture& texture, const std::string& filepath) {
    if (!texture.loadFromFile(filepath)) {
        std::cerr << "cannot load texture " << filepath << std::endl;
    }
}

void Resource_Management::loadFont(sf::Font& font, const std::string& filepath) {
    if (!font.openFromFile(filepath)) {
        std::cerr << "cannot load texture " << filepath << std::endl;
    }
}

void Resource_Management::loadSound(sf::SoundBuffer& buffer, const std::string& filepath) {
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "cannot load texture " << filepath << std::endl;
    }
}

const unsigned int Resource_Management::WINDOW_WIDTH = 540;
const unsigned int Resource_Management::WINDOW_HEIGHT = 360;

sf::Color Resource_Management::buttonShapeFillColor = sf::Color(111, 111, 111);
sf::Color Resource_Management::colorWhenClickOnButton = sf::Color(125, 134, 189);