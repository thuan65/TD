#include "game.h"
#include <string>
#include <SFML/Graphics/Sprite.hpp> // Include đầy đủ

game::game()
    : window(sf::VideoMode({ 540, 360 }), "GAME"),
    gameMap(Resource_Management::getTexture("Map_Game1")),
    towerControl(&bulletManager),
    isBuildMenuOpen(false), // << Khởi tạo trạng thái menu
    lives(5), money(500), currentWave(0),
    isGameOver(false), playerWon(false)
{
    
    window.setFramerateLimit(60);
    setupBuildMenu(); // Gọi hàm thiết lập menu
    updateGUISprites(); // Gọi lần đầu để khởi tạo sprites

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
    point s = { 1,0,0 }, e = { 8 , 15 ,0 };
    PathFinder::setStart(s); PathFinder::setEnd(e);
    PathFinder::findPath(_Map_Game_Logic);
    
}

void game::setupBuildMenu() {
    // Thiết lập nền cho menu
    buildMenuBackground = std::make_unique<sf::RectangleShape>();
    buildMenuBackground->setSize({ 148.f, 37.f });
    buildMenuBackground->setFillColor(sf::Color(100, 100, 100, 200));

    // Tạo các sprite cho icon bằng make_unique
    // Lưu ý: Cần đảm bảo "Tower1_Icon" và "Tower2_Icon" đã được load trong Resource_Management
    const sf::Texture& icon1Tex = Resource_Management::getTexture("Tower1_Icon")[0];
    buildMenuTower1Icon = std::make_unique<sf::Sprite>(icon1Tex);

    const sf::Texture& icon2Tex = Resource_Management::getTexture("Tower2_Icon")[0];
    buildMenuTower2Icon = std::make_unique<sf::Sprite>(icon2Tex);


    const sf::Texture& icon3Tex = Resource_Management::getTexture("Tower3_Icon")[0];
    buildMenuTower3Icon = std::make_unique<sf::Sprite>(icon3Tex);


    const sf::Texture& icon4Tex = Resource_Management::getTexture("Tower4_Icon")[0];
    buildMenuTower4Icon = std::make_unique<sf::Sprite>(icon4Tex);
}

void game::openBuildMenu(int row, int col) {
    isBuildMenuOpen = true;
    buildMenuTilePosition = { row, col };

    // Tính toán vị trí để vẽ menu lên màn hình
    float menuX = static_cast<float>((col + 1) * point::TileSize);
    float menuY = static_cast<float>(row * point::TileSize);

    buildMenuBackground->setPosition(sf::Vector2f(menuX, menuY));
    // Dùng -> để gọi hàm trên con trỏ
    buildMenuTower1Icon->setPosition(sf::Vector2f(menuX + 5.f, menuY + 2.5f));  
    buildMenuTower2Icon->setPosition(sf::Vector2f(menuX + 42.f, menuY + 2.5f));
    buildMenuTower3Icon->setPosition(sf::Vector2f(menuX + 79.f, menuY + 2.5f)); // Icon 3 (42 + 32 + 5)
    buildMenuTower4Icon->setPosition(sf::Vector2f(menuX + 116.f, menuY + 2.5f)); // Icon 4 (79 + 32 + 5)



    // Cập nhật vùng có thể click cho các icon
    tower1IconBounds = buildMenuTower1Icon->getGlobalBounds();
    tower2IconBounds = buildMenuTower2Icon->getGlobalBounds();
    tower3IconBounds = buildMenuTower3Icon->getGlobalBounds();
    tower4IconBounds = buildMenuTower4Icon->getGlobalBounds();
}

void game::closeBuildMenu() {
    isBuildMenuOpen = false;
}

void game::updateGUISprites() {
    std::cout << "Updating GUI Sprites. Current lives: " << lives << std::endl;

    livesSprites.clear();
    const sf::Texture& heartTex = Resource_Management::getTexture("Heart_Icon")[0];

    // ĐỊNH NGHĨA TỶ LỆ Ở MỘT CHỖ ĐỂ DỄ THAY ĐỔI
    const float heartScale = 0.01f;

    for (int i = 0; i < lives; ++i) {
        sf::Sprite heartSprite(heartTex);
        heartSprite.setScale(sf::Vector2f(heartScale, heartScale));

        // --- SỬA LẠI CÁCH TÍNH TOÁN VỊ TRÍ ---
        // Lấy chiều rộng GỐC từ texture và nhân với tỷ lệ
        float scaledHeartWidth = heartTex.getSize().x * heartScale;

        // Dùng chiều rộng đã tính để đặt vị trí
        heartSprite.setPosition({ 10.f + i * (scaledHeartWidth + 5), 10.f });

        livesSprites.push_back(heartSprite);
    }

    drawNumber(money, 300.f, 10.f, moneySprites);
    drawNumber(currentWave, 150.f, 10.f, waveSprites);

}
// Hàm phụ để vẽ một con số từ các sprite
void game::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
    sprite_vector.clear();
    std::string numStr = std::to_string(number);
    float currentX = x;
    for (char c : numStr) {
        int digit = c - '0'; // Chuyển ký tự '0'-'9' thành số 0-9
        const sf::Texture& tex = Resource_Management::Digits[digit][0];
        sf::Sprite sprite(tex);
        sprite.setPosition({ currentX, y });
        sprite_vector.push_back(sprite);
        currentX += tex.getSize().x; // Dịch sang phải để vẽ chữ số tiếp theo
    }
}
    
game::~game() {}

void game::Run() {
    vector<vector<point>> _Map_Game_Logic = gameMap.getMap_Game();

    // Khởi tạo trạng thái game lúc bắt đầu
    currentWave = 1;
    waveControl.startNewWave();
    updateGUISprites(); // Cập nhật hình ảnh GUI lần đầu

    sf::Clock clock;
    while (window.isOpen()) {
        // --- XỬ LÝ SỰ KIỆN (INPUT) ---
        if (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            // Chỉ xử lý input nếu game chưa kết thúc
            else if (!isGameOver && !playerWon && event->is<sf::Event::MouseButtonPressed>())
            {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i pixelPos = mouseEvent->position;
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                    if (isBuildMenuOpen) {
                        if (tower1IconBounds.contains(worldPos)) {
                            // Logic trừ tiền khi xây trụ
                            if (money >= 100) { // Giả sử trụ 1 giá 100
                                money -= 100;
                                towerControl.buildTower(buildMenuTilePosition.y, buildMenuTilePosition.x, "Tower1");
                                updateGUISprites(); // Cập nhật lại sprite tiền
                            }
                            closeBuildMenu();
                        }
                        else if (tower2IconBounds.contains(worldPos)) {
                            if (money >= 150) { // Giả sử trụ 2 giá 150
                                money -= 150;
                                towerControl.buildTower(buildMenuTilePosition.y, buildMenuTilePosition.x, "Tower2");
                                updateGUISprites();
                            }
                            closeBuildMenu();
                        }
                        // Thêm logic cho trụ 3, 4 nếu cần
                        else {
                            closeBuildMenu();
                        }
                    }
                    else {
                        int row = static_cast<int>(worldPos.y / point::TileSize);
                        int col = static_cast<int>(worldPos.x / point::TileSize);

                        if (row >= 0 && row < _Map_Game_Logic.size() && col >= 0 && col < _Map_Game_Logic[0].size()) {
                            if (_Map_Game_Logic[row][col].getC() == point::Empty_Tile) {
                                openBuildMenu(row, col);
                            }
                        }
                    }

                    // Bắt đầu wave mới (nên có nút riêng, tạm thời vẫn dùng click)
                    if (waveControl.WaveEnded()) {
                        if (currentWave < WaveManager::TOTAL_WAVES) {
                            waveControl.startNewWave();
                            currentWave++;
                            updateGUISprites(); // Cập nhật lại sprite wave
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // --- CẬP NHẬT LOGIC GAME ---
        // Chỉ cập nhật nếu game đang diễn ra
        if (!isGameOver && !playerWon) {
            waveControl.update(deltaTime);
            towerControl.update(deltaTime, waveControl.getActiveEnemy());
            bulletManager.update(deltaTime, waveControl.getActiveEnemy());
            gameMap.Update(deltaTime);

            // Xử lý quái bị xóa (do chết hoặc về đích)
            int enemiesReachedEnd = 0;
            int moneyFromKills = 0;
            waveControl.processRemovals(&enemiesReachedEnd, &moneyFromKills); // Sửa WaveManager để nhận con trỏ

            // Cập nhật mạng
            if (enemiesReachedEnd > 0) {
                lives -= enemiesReachedEnd;
                updateGUISprites();
                if (lives <= 0) {
                    lives = 0;
                    isGameOver = true;
                }
            }

            // Cập nhật tiền
            if (moneyFromKills > 0) {
                money += moneyFromKills;
                updateGUISprites();
            }

            // Kiểm tra điều kiện thắng
            if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
                playerWon = true;
            }
        }


        // --- VẼ MỌI THỨ ---
        window.clear();
        gameMap.draw(window);
        waveControl.draw(window);
        towerControl.draw(window);
        bulletManager.draw(window);

         //Vẽ menu nếu nó đang mở
        if (isBuildMenuOpen) {
            if (buildMenuBackground) window.draw(*buildMenuBackground);
            if (buildMenuTower1Icon) window.draw(*buildMenuTower1Icon);
            if (buildMenuTower2Icon) window.draw(*buildMenuTower2Icon);
            if (buildMenuTower3Icon) window.draw(*buildMenuTower3Icon);
            if (buildMenuTower4Icon) window.draw(*buildMenuTower4Icon);
        }

        //// Vẽ GUI bằng sprite
        for (const auto& sprite : livesSprites) window.draw(sprite);
      /*  for (const auto& sprite : moneySprites) window.draw(sprite);
        for (const auto& sprite : waveSprites) window.draw(sprite);*/

        //// Vẽ thông báo kết thúc game
        if (isGameOver && gameOverSprite) window.draw(*gameOverSprite);
        if (playerWon && victorySprite) window.draw(*victorySprite);

        window.display();
    }
}