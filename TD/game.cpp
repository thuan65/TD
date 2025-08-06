//#include "game.h"
//#include <string>
//#include <SFML/Graphics.hpp> // Include đầy đủ
//
//// --- HÀM CONSTRUCTOR ---
//game::game()
//    : window(sf::VideoMode({ 540, 360 }), "GAME"),
//    gameMap(Resource_Management::getTexture("Map_Game1")),
//    towerControl(&window, &bulletManager),
//    mapSelection(&gameMap, &bulletManager, &waveControl, &towerControl),
//
//    // Khởi tạo các biến trạng thái
//    lives(5), money(500), currentWave(0),
//    isGameOver(false), playerWon(false),
//    timeUntilNextWave(TIME_BETWEEN_WAVES) {
//    //window.setFramerateLimit(60);
//
//    updateGUISprites(); // Gọi để khởi tạo các sprite GUI ban đầu
//
//    // Thiết lập sprite cho Game Over và Victory
//    const sf::Texture& victoryTex = Resource_Management::getTexture("Victory_Image")[0];
//    victorySprite = std::make_unique<sf::Sprite>(victoryTex);
//    sf::FloatRect vicBounds = victorySprite->getLocalBounds();
//    victorySprite->setOrigin(sf::Vector2f(vicBounds.size.x / 2.f, vicBounds.size.y / 2.f));
//    victorySprite->setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
//
//    const sf::Texture& goTex = Resource_Management::getTexture("GameOver_Image")[0];
//    gameOverSprite = std::make_unique<sf::Sprite>(goTex);
//    sf::FloatRect goBounds = gameOverSprite->getLocalBounds();
//    gameOverSprite->setOrigin(sf::Vector2f(goBounds.size.x / 2.f, goBounds.size.y / 2.f));
//    gameOverSprite->setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
//
//
//}
//
//// --- HÀM HỦY ---
//game::~game() {}
//
//// --- CÁC HÀM TRỢ GIÚP ---
//void game::updateGUISprites() {
//    livesSprites.clear();
//    const sf::Texture& heartTex = Resource_Management::getTexture("Heart_Icon")[0];
//    const float heartScale = 0.01f; // Bạn có thể chỉnh size ở đây
//    for (int i = 0; i < lives; ++i) {
//        sf::Sprite heartSprite(heartTex);
//        heartSprite.setScale(sf::Vector2f(heartScale, heartScale));
//        float scaledHeartWidth = heartTex.getSize().x * heartScale;
//        heartSprite.setPosition({ 10.f + i * (scaledHeartWidth + 5), 10.f });
//        livesSprites.push_back(heartSprite);
//    }
//    drawNumber(money, 300.f, 10.f, moneySprites);
//    drawNumber(currentWave, 150.f, 10.f, waveSprites);
//}
//
//void game::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
//    sprite_vector.clear();
//    std::string numStr = std::to_string(number);
//    float currentX = x;
//
//    // Bạn có thể chỉnh sửa con số này để thay đổi kích thước
//    const float digitScale = 0.04f;
//
//    for (char c : numStr) {
//        int digit = c - '0';
//        const sf::Texture& tex = Resource_Management::Digits[digit][0];
//        sf::Sprite sprite(tex);
//
//        // --- THÊM DÒNG QUAN TRỌNG NÀY ---
//        sprite.setScale(sf::Vector2f(digitScale, digitScale));
//
//        sprite.setPosition({ currentX, y });
//        sprite_vector.push_back(sprite);
//
//        // --- SỬA LẠI DÒNG NÀY ---
//        // Phải tính khoảng cách dựa trên kích thước đã được scale
//        currentX += tex.getSize().x * digitScale;
//    }
//}
//// --- HÀM RUN CHÍNH ---
//void game::Run() {
//    vector<vector<point>> _Map_Game_Logic = gameMap.getMap_Game();
//    currentWave = 1;
//    mapSelection.selectMap(PlayState::Map1); // This is for selecting map MOVE THIS TO THE LOOP AFTER For now map 1 is set
//    waveControl.startNewWave();
//  
//    sf::Clock clock;
//    while (window.isOpen()) {
//        //////////////All of Part is the in game when playing/////////////////////
//        if (const auto event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>()) {
//                window.close();
//            }
//
//            if (!isGameOver && !playerWon && event->is<sf::Event::MouseButtonPressed>()) {
//                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
//                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
//                    //Add a switch case here for later use (Event handler or smth)
//                    sf::Vector2i pixelPos = mouseEvent->position;
//                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
//                    towerControl.resolveTowerAt(worldPos, money);
//                    updateGUISprites(); // Cập nhật lại hiển thị tiền
//                }
//
//                if (waveControl.WaveEnded()) {
//                    if (currentWave < WaveManager::TOTAL_WAVES) {
//                        waveControl.startNewWave();
//                        currentWave++;
//                        updateGUISprites();
//                    }
//                }
//            }
//        }
//
//
//        float deltaTime = clock.restart().asSeconds();
//
//        if (!isGameOver && !playerWon) {
//            if (waveControl.WaveEnded() && !isBetweenWaves) {
//                // Nếu wave vừa kết thúc và chưa bắt đầu đếm ngược
//                if (currentWave < WaveManager::TOTAL_WAVES) {
//                    // Bắt đầu trạng thái nghỉ
//                    isBetweenWaves = true;
//                    timeUntilNextWave = TIME_BETWEEN_WAVES;
//                }
//            }
//
//            // Nếu đang trong thời gian nghỉ, bắt đầu đếm ngược
//            if (isBetweenWaves) {
//                timeUntilNextWave -= deltaTime;
//                // Cập nhật sprite hiển thị thời gian
//                drawNumber(static_cast<int>(timeUntilNextWave) + 1, 250.f, 40.f, nextWaveTimerSprites);
//
//                if (timeUntilNextWave <= 0) {
//                    isBetweenWaves = false; // Kết thúc đếm ngược
//                    currentWave++;
//                    waveControl.startNewWave();
//                    updateGUISprites();
//                }
//            }
//          
//            waveControl.update(deltaTime);
//            towerControl.update(deltaTime, waveControl.getActiveEnemy());
//            bulletManager.update(deltaTime, waveControl.getActiveEnemy());
//            gameMap.Update(deltaTime);
//            	
//            int enemiesReachedEnd = 0;
//            int moneyFromKills = 0;
//            waveControl.processRemovals(&enemiesReachedEnd, &moneyFromKills);
//
//            if (enemiesReachedEnd > 0) {
//                lives -= enemiesReachedEnd;
//                updateGUISprites();
//                if (lives <= 0) {
//                    lives = 0;
//                    isGameOver = true;
//                }
//            }
//            if (moneyFromKills > 0) {
//                money += moneyFromKills;
//                updateGUISprites();
//            }
//            if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
//                playerWon = true;
//            }
//        }
//
//        window.clear();
//        gameMap.draw(window);
//        waveControl.draw(window);
//        towerControl.draw(window);
//        bulletManager.draw(window);
//
//        for (const auto& sprite : livesSprites) window.draw(sprite);
//        for (const auto& sprite : moneySprites) window.draw(sprite);
//        for (const auto& sprite : waveSprites) window.draw(sprite);
//        if (isBetweenWaves) {
//            for (const auto& sprite : nextWaveTimerSprites) {
//                window.draw(sprite);
//            }
//        }
//
//        if (isGameOver && gameOverSprite) window.draw(*gameOverSprite);
//        if (playerWon && victorySprite) window.draw(*victorySprite);
//
//
//
//
//        window.display();
//    }
//    //////////////All of Part is the in game/////////////////////
//}

#include "game.h"
#include <string>
#include <SFML/Graphics.hpp>

// --- HÀM CONSTRUCTOR ---
game::game()
    : window(sf::VideoMode({ 540, 360 }), "GAME"),
    gameMap(Resource_Management::getTexture("Map_Game1")),
    towerControl(&window, &bulletManager), // Truyền window vào TowerManager
    mapSelection(&gameMap, &bulletManager, &waveControl, &towerControl),
    lives(5), money(500), currentWave(0),
    isGameOver(false), playerWon(false),
    isBetweenWaves(false), timeUntilNextWave(0.f)
{
    //window.setFramerateLimit(60);
    updateGUISprites();

    

    //Thiết lập sprite cho Game Over và Victory
    const sf::Texture& victoryTex = Resource_Management::getTexture("Victory_Image")[0];
    victorySprite = std::make_unique<sf::Sprite>(victoryTex);
    sf::FloatRect vicBounds = victorySprite->getLocalBounds();
    victorySprite->setOrigin(sf::Vector2f(vicBounds.size.x / 2.f, vicBounds.size.y / 2.f));
    victorySprite->setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });

    const sf::Texture& goTex = Resource_Management::getTexture("GameOver_Image")[0];
    gameOverSprite = std::make_unique<sf::Sprite>(goTex);
    sf::FloatRect goBounds = gameOverSprite->getLocalBounds();
    gameOverSprite->setOrigin(sf::Vector2f(goBounds.size.x / 2.f, goBounds.size.y / 2.f));
    gameOverSprite->setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });

}

// --- HÀM HỦY ---

game::~game() {}

// --- CÁC HÀM TRỢ GIÚP ---
void game::updateGUISprites() {
    // ... code updateGUISprites của bạn (giữ nguyên) ...
}

void game::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
    // ... code drawNumber của bạn (giữ nguyên) ...
}

// --- HÀM RUN CHÍNH ---
void game::Run() {
    vector<vector<point>> _Map_Game_Logic = gameMap.getMap_Game();

    // Bắt đầu đếm ngược cho wave đầu tiên
    isBetweenWaves = true;
    timeUntilNextWave = TIME_BETWEEN_WAVES;
    currentWave = 0;
    mapSelection.selectMap(PlayState::Map1);

    sf::Clock clock;
    while (window.isOpen()) {
        if (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (!isGameOver && !playerWon && event->is<sf::Event::MouseButtonPressed>())
            {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i pixelPos = mouseEvent->position;
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                    // Giao toàn bộ việc xử lý click cho TowerManager
                    towerControl.handleMouseClick(worldPos, money);

                    // Cập nhật lại GUI sau khi có thể đã tiêu tiền
                    updateGUISprites();
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (!isGameOver && !playerWon) {
            if (waveControl.WaveEnded() && !isBetweenWaves && currentWave > 0) {
                if (currentWave < WaveManager::TOTAL_WAVES) {
                    isBetweenWaves = true;
                    timeUntilNextWave = TIME_BETWEEN_WAVES;
                }
            }

            if (isBetweenWaves) {
                timeUntilNextWave -= deltaTime;
                drawNumber(static_cast<int>(timeUntilNextWave) + 1, 250.f, 40.f, nextWaveTimerSprites);
                if (timeUntilNextWave <= 0) {
                    isBetweenWaves = false;
                    currentWave++;
                    waveControl.startNewWave(); // Dùng startWave(int)
                    updateGUISprites();
                }
            }

            waveControl.update(deltaTime);
            towerControl.update(deltaTime, waveControl.getActiveEnemy());
            bulletManager.update(deltaTime, waveControl.getActiveEnemy());
            gameMap.Update(deltaTime);

            int enemiesReachedEnd = 0;
            int moneyFromKills = 0;
            waveControl.processRemovals(&enemiesReachedEnd, &moneyFromKills);

            if (enemiesReachedEnd > 0) {
                lives -= enemiesReachedEnd;
                updateGUISprites();
                if (lives <= 0) { lives = 0; isGameOver = true; }
            }
            if (moneyFromKills > 0) {
                money += moneyFromKills;
                updateGUISprites();
            }
            if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
                playerWon = true;
            }
        }

        // --- VẼ MỌI THỨ ---
        window.clear();
        gameMap.draw(window);
        waveControl.draw(window);
        towerControl.draw(window); // TowerManager tự vẽ menu
        bulletManager.draw(window);

        for (const auto& sprite : livesSprites) window.draw(sprite);
        for (const auto& sprite : moneySprites) window.draw(sprite);
        for (const auto& sprite : waveSprites) window.draw(sprite);

        if (isBetweenWaves) {
            for (const auto& sprite : nextWaveTimerSprites) window.draw(sprite);
        }

        if (isGameOver && gameOverSprite) window.draw(*gameOverSprite);
        if (playerWon && victorySprite) window.draw(*victorySprite);

        window.display();
    }
}