#include "game.h"
#include <string>
#include <SFML/Graphics.hpp> // Include đầy đủ

// --- HÀM CONSTRUCTOR ---
game::game()
    : window(sf::VideoMode({ 540, 360 }), "GAME"),
    gameMap(Resource_Management::getTexture("Map_Game1")),
    towerControl(&bulletManager),
    mapSelection(&gameMap, &bulletManager, &waveControl, &towerControl),
    isBuildMenuOpen(false),
    // Khởi tạo các biến trạng thái
    lives(5), money(500), currentWave(0),
    isGameOver(false), playerWon(false),
    timeUntilNextWave(TIME_BETWEEN_WAVES) {
    //window.setFramerateLimit(60);
    setupBuildMenu();
    updateGUISprites(); // Gọi để khởi tạo các sprite GUI ban đầu

    // Thiết lập sprite cho Game Over và Victory
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

    // Tính toán đường đi ban đầu
    vector<vector<point>> _Map_Game_Logic = gameMap.getMap_Game();
    point s = { 3,0,0 }, e = { 8 , 15 ,0 };
    PathFinder::setStart(s); PathFinder::setEnd(e);
    PathFinder::findPath(_Map_Game_Logic);
}

// --- HÀM HỦY ---
game::~game() {}

// --- CÁC HÀM TRỢ GIÚP ---
void game::setupBuildMenu() {
    buildMenuBackground = std::make_unique<sf::RectangleShape>();
    buildMenuBackground->setSize({ 148.f, 37.f });
    buildMenuBackground->setFillColor(sf::Color(100, 100, 100, 200));

    buildMenuTower1Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower1_Icon")[0]);
    buildMenuTower2Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower2_Icon")[0]);
    buildMenuTower3Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower3_Icon")[0]);
    buildMenuTower4Icon = std::make_unique<sf::Sprite>(Resource_Management::getTexture("Tower4_Icon")[0]);
}
// game.cpp

void game::openBuildMenu(int row, int col) {
    isBuildMenuOpen = true;
    buildMenuTilePosition = { col, row }; // Gán vị trí ô đất (x=col, y=row)

    // --- TÍNH TOÁN LẠI VỊ TRÍ MENU ---

    // 1. Lấy tọa độ tâm của ô đất đã click
    float tileCenterX = static_cast<float>(col * point::TileSize) + (point::TileSize / 2.f);
    float tileCenterY = static_cast<float>(row * point::TileSize) + (point::TileSize / 2.f);

    // 2. Lấy kích thước của nền menu
    sf::Vector2f menuSize = buildMenuBackground->getSize();

    // 3. Tính toán vị trí góc trên-trái của menu để nó được CĂN GIỮA
    // so với tâm ô đất và nằm ngay PHÍA TRÊN ô đất
    float menuX = tileCenterX - (menuSize.x / 2.f);
    float menuY = tileCenterY - (point::TileSize / 2.f) - menuSize.y - 5.f; // 5.f là khoảng đệm

    // Đảm bảo menu không bị vẽ ra ngoài màn hình
    const sf::Vector2u windowSize = window.getSize();
    if (menuX < 0) menuX = 0;
    if (menuY < 0) menuY = 0;
    if (menuX + menuSize.x > windowSize.x) menuX = windowSize.x - menuSize.x;
    if (menuY + menuSize.y > windowSize.y) menuY = windowSize.y - menuSize.y;


    // 4. Đặt vị trí cho nền và các icon
    buildMenuBackground->setPosition(sf::Vector2f(menuX, menuY));

    // Vị trí các icon được tính dựa trên vị trí mới của menu
    buildMenuTower1Icon->setPosition(sf::Vector2f(menuX + 5.f, menuY + 2.5f));
    buildMenuTower2Icon->setPosition(sf::Vector2f(menuX + 42.f, menuY + 2.5f));
    buildMenuTower3Icon->setPosition(sf::Vector2f(menuX + 79.f, menuY + 2.5f));
    buildMenuTower4Icon->setPosition(sf::Vector2f(menuX + 116.f, menuY + 2.5f));

    // Cập nhật lại vùng clickable
   /* tower1IconBounds = buildMenuTower1Icon->getGlobalBounds();
    tower2IconBounds = buildMenuTower2Icon->getGlobalBounds();
    tower3IconBounds = buildMenuTower3Icon->getGlobalBounds();
    tower4IconBounds = buildMenuTower4Icon->getGlobalBounds();*/
}
void game::closeBuildMenu() {
    isBuildMenuOpen = false;
}

void game::updateGUISprites() {
    livesSprites.clear();
    const sf::Texture& heartTex = Resource_Management::getTexture("Heart_Icon")[0];
    const float heartScale = 0.01f; // Bạn có thể chỉnh size ở đây
    for (int i = 0; i < lives; ++i) {
        sf::Sprite heartSprite(heartTex);
        heartSprite.setScale(sf::Vector2f(heartScale, heartScale));
        float scaledHeartWidth = heartTex.getSize().x * heartScale;
        heartSprite.setPosition({ 10.f + i * (scaledHeartWidth + 5), 10.f });
        livesSprites.push_back(heartSprite);
    }
    drawNumber(money, 300.f, 10.f, moneySprites);
    drawNumber(currentWave, 150.f, 10.f, waveSprites);
}

void game::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
    sprite_vector.clear();
    std::string numStr = std::to_string(number);
    float currentX = x;

    // Bạn có thể chỉnh sửa con số này để thay đổi kích thước
    const float digitScale = 0.04f;

    for (char c : numStr) {
        int digit = c - '0';
        const sf::Texture& tex = Resource_Management::Digits[digit][0];
        sf::Sprite sprite(tex);

        // --- THÊM DÒNG QUAN TRỌNG NÀY ---
        sprite.setScale(sf::Vector2f(digitScale, digitScale));

        sprite.setPosition({ currentX, y });
        sprite_vector.push_back(sprite);

        // --- SỬA LẠI DÒNG NÀY ---
        // Phải tính khoảng cách dựa trên kích thước đã được scale
        currentX += tex.getSize().x * digitScale;
    }
}
// --- HÀM RUN CHÍNH ---
void game::Run() {
    vector<vector<point>> _Map_Game_Logic = gameMap.getMap_Game();
    currentWave = 1;
    mapSelection.selectMap(1); // This is for selecting map MOVE THIS TO THE LOOP AFTER
    waveControl.startNewWave();

    sf::Clock clock;
    while (window.isOpen()) {
        if (const auto event = window.pollEvent()) {
            sf::Vector2i orldPos = sf::Mouse::getPosition(window);
            //std::cout << "Mouse " << orldPos.x << " " << orldPos.y << "\n";
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (!isGameOver && !playerWon && event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2i pixelPos = mouseEvent->position;
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                  
                    if (isBuildMenuOpen) {
                        // TÍNH TOÁN BOUNDS NGAY TẠI ĐÂY
                        if (buildMenuTower1Icon->getGlobalBounds().contains(worldPos)) {
                            if (money >= 100) {
                                money -= 100;
                                towerControl.buildTower(worldPos, "Tower1");
                                updateGUISprites(); // Cập nhật lại hiển thị tiền
                            }
                            closeBuildMenu();
                        }
                        else if (buildMenuTower2Icon->getGlobalBounds().contains(worldPos)) {
                            if (money >= 150) {
                                money -= 150;
                                towerControl.buildTower(worldPos, "Tower2");
                                updateGUISprites(); // Cập nhật lại hiển thị tiền
                            }

                            closeBuildMenu();
                        }
                        else if (buildMenuTower3Icon->getGlobalBounds().contains(worldPos)) {
                            if (money >= 200) {
                                money -= 200;
                                towerControl.buildTower(worldPos, "Tower3");
                                updateGUISprites(); // Cập nhật lại hiển thị tiền
                            }

                            closeBuildMenu();
                        }
                        else if (buildMenuTower4Icon->getGlobalBounds().contains(worldPos)) {
                            if (money >= 250) {
                                money -= 250;
                                towerControl.buildTower(worldPos, "Tower4");
                                updateGUISprites(); // Cập nhật lại hiển thị tiền
                            }

                            closeBuildMenu();
                        }
                        else {
                            closeBuildMenu();
                        }
                    }
                    else {
                        int row = static_cast<int>(worldPos.y / point::TileSize);
                        int col = static_cast<int>(worldPos.x / point::TileSize);

                        if (row >= 0 && row < _Map_Game_Logic.size() && col >= 0 && col < _Map_Game_Logic[0].size()) {
                            if (towerControl.clickCheck(worldPos)) {
                                openBuildMenu(row, col);
                            }
                        }
                    }

                    if (waveControl.WaveEnded()) {
                        if (currentWave < WaveManager::TOTAL_WAVES) {
                            waveControl.startNewWave();
                            currentWave++;
                            updateGUISprites();
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (!isGameOver && !playerWon) {
            if (waveControl.WaveEnded() && !isBetweenWaves) {
                // Nếu wave vừa kết thúc và chưa bắt đầu đếm ngược
                if (currentWave < WaveManager::TOTAL_WAVES) {
                    // Bắt đầu trạng thái nghỉ
                    isBetweenWaves = true;
                    timeUntilNextWave = TIME_BETWEEN_WAVES;
                }
            }

            // Nếu đang trong thời gian nghỉ, bắt đầu đếm ngược
            if (isBetweenWaves) {
                timeUntilNextWave -= deltaTime;
                // Cập nhật sprite hiển thị thời gian
                drawNumber(static_cast<int>(timeUntilNextWave) + 1, 250.f, 40.f, nextWaveTimerSprites);

                if (timeUntilNextWave <= 0) {
                    isBetweenWaves = false; // Kết thúc đếm ngược
                    currentWave++;
                    waveControl.startNewWave();
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
                if (lives <= 0) {
                    lives = 0;
                    isGameOver = true;
                }
            }
            if (moneyFromKills > 0) {
                money += moneyFromKills;
                updateGUISprites();
            }
            if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
                playerWon = true;
            }
        }

        window.clear();
        gameMap.draw(window);
        waveControl.draw(window);
        towerControl.draw(window);
        bulletManager.draw(window);

        // for (int i = 0; i < _Map_Game_Logic.size(); ++i) {
         //    for (int j = 0; j < _Map_Game_Logic[0].size(); ++j) {
         //        sf::RectangleShape cell(sf::Vector2f(point::TileSize, point::TileSize));
         //        cell.setPosition(sf::Vector2f(j * point::TileSize, i * point::TileSize));
         //        cell.setOutlineColor(sf::Color::White);
         //        cell.setOutlineThickness(1);
         //        cell.setFillColor(sf::Color::Transparent);
          //       window.draw(cell);
          //   }
         //}

        if (isBuildMenuOpen) {
            if (buildMenuBackground) window.draw(*buildMenuBackground);
            if (buildMenuTower1Icon) window.draw(*buildMenuTower1Icon);
            if (buildMenuTower2Icon) window.draw(*buildMenuTower2Icon);
            if (buildMenuTower3Icon) window.draw(*buildMenuTower3Icon);
            if (buildMenuTower4Icon) window.draw(*buildMenuTower4Icon);
        }

        for (const auto& sprite : livesSprites) window.draw(sprite);
        for (const auto& sprite : moneySprites) window.draw(sprite);
        for (const auto& sprite : waveSprites) window.draw(sprite);
        if (isBetweenWaves) {
            for (const auto& sprite : nextWaveTimerSprites) {
                window.draw(sprite);
            }
        }

        if (isGameOver && gameOverSprite) window.draw(*gameOverSprite);
        if (playerWon && victorySprite) window.draw(*victorySprite);

        window.display();
    }
}