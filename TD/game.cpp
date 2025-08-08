//#include "game.h"
//#include <string>
//#include <SFML/Graphics.hpp> // Include đầy đủ
//
//
//// --- HÀM CONSTRUCTOR ---
//game::game()
//    : window(sf::VideoMode({ 540, 360 }), "GAME"),
//    gameMap(Resource_Management::getTexture("Map_Game1")),
//    waveControl(),
//    bulletManager(&waveControl),
//    towerControl(&window, &bulletManager),
//    mapSelection(&gameMap, &bulletManager, &waveControl, &towerControl),
//   
//
//    // Khởi tạo các biến trạng thái
//    lives(5), money(500), currentWave(0),
//    isGameOver(false), playerWon(false),
//    timeUntilNextWave(TIME_BETWEEN_WAVES)
//{
//    towerControl.setWaveManager(&waveControl);
//    //window.setFramerateLimit(60);
//
//    updateGUISprites(); // Gọi để khởi tạo các sprite GUI ban đầu
//
//    // Thiết lập sprite cho Game Over và Victory
//    //const sf::Texture& victoryTex = Resource_Management::getTexture("Victory_Image")[0];
//    //victorySprite = std::make_unique<sf::Sprite>(victoryTex);
//    //sf::FloatRect vicBounds = victorySprite->getLocalBounds();
//    //victorySprite->setOrigin(sf::Vector2f(vicBounds.size.x / 2.f, vicBounds.size.y / 2.f));
//    //victorySprite->setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
//
//    //const sf::Texture& goTex = Resource_Management::getTexture("GameOver_Image")[0];
//    //gameOverSprite = std::make_unique<sf::Sprite>(goTex);
//    //sf::FloatRect goBounds = gameOverSprite->getLocalBounds();
//    //gameOverSprite->setOrigin(sf::Vector2f(goBounds.size.x / 2.f, goBounds.size.y / 2.f));
//    //gameOverSprite->setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
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
//void game::handleWaveTiming(float deltaTime) {
//    if (waveControl.WaveEnded() && !isBetweenWaves) {
//        // Nếu wave vừa kết thúc và chưa bắt đầu đếm ngược
//        if (currentWave < WaveManager::TOTAL_WAVES) {
//            // Bắt đầu trạng thái nghỉ
//            isBetweenWaves = true;
//            timeUntilNextWave = TIME_BETWEEN_WAVES;
//        }
//    }
//
//    // Nếu đang trong thời gian nghỉ, bắt đầu đếm ngược
//    if (isBetweenWaves) {
//        timeUntilNextWave -= deltaTime;
//        // Cập nhật sprite hiển thị thời gian
//        drawNumber(static_cast<int>(timeUntilNextWave) + 1, 250.f, 40.f, nextWaveTimerSprites);
//
//        if (timeUntilNextWave <= 0) {
//            isBetweenWaves = false; // Kết thúc đếm ngược
//            currentWave++;
//            waveControl.startWave(currentWave);
//            updateGUISprites();
//        }
//    }
//    if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
//        playerWon = true;
//    }
//}
//void game::handleEnemyResults() {
//    auto result = waveControl.processRemovals();
//    if (result.enemiesReachedEnd > 0) {
//        lives -= result.enemiesReachedEnd;
//        updateGUISprites();
//        if (lives <= 0) {
//            lives = 0;
//            isGameOver = true;
//        }
//    }
//    if (result.moneyFromKills > 0) {
//        money += result.moneyFromKills;
//        updateGUISprites();
//    }
//}
//// --- HÀM RUN CHÍNH ---
//void game::Run() {
//  //  GameSaver gameSave(this);
//
//    mapSelection.selectMap(MapID::Map1);
//  
//    sf::Clock clock;
//    while (window.isOpen()) {
//        //////////////All of Part is the in game when playing/////////////////////
//        if (const auto event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>()) {
//                window.close();
//            }
//
//            if (!isGameOver && !playerWon) {
//                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
//                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
//                   
//
//                
//
//                    sf::Vector2i pixelPos = mouseEvent->position;
//                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
//                    towerControl.resolveTowerAt(worldPos, money);
//                    //updateGUISprites(); // Cập nhật lại hiển thị tiền
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
//        
//    
//            waveControl.update(deltaTime);
//            towerControl.update(deltaTime);
//            bulletManager.update(deltaTime);
//            gameMap.Update(deltaTime);
//       
//          
//           
//
//            
//           
//        }
//
//       
//
//       //if (isGameOver && gameOverSprite) window.draw(*gameOverSprite);
//       //if (playerWon && victorySprite) window.draw(*victorySprite);
//
//      
//       
//        
//
//        window.display();
//    }
//    //////////////All of Part is the in game/////////////////////
//}


#include "game.h"

void game::initResources() {

}

void game::initWindow() {
	window = sf::RenderWindow(sf::VideoMode({ 540, 360 }), "Tower Defense");
	window.setFramerateLimit(60);
}

void game::initStates() {
	initMainMenuState();
}

void game::handleEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (!states.empty()) {
			states.top()->handleInput(event);
		}
	}
}

void game::update(float dt) {
	if (!states.empty()) {
		if (states.top()->shouldAllowUpdateBelow() && states.size() >= 2) {
			std::unique_ptr<State> temp = std::move(states.top());
			states.pop();
			states.top()->update(dt);
			states.push(std::move(temp));
		}
		states.top()->update(dt);
	}
}

void game::render() {
	window.clear();

	if (!states.empty()) {
		if (states.top()->shouldAllowRenderBelow() && states.size() >= 2) {
			std::unique_ptr<State> temp = std::move(states.top());
			states.pop();
			states.top()->render();
			states.push(std::move(temp));
		}
		states.top()->render();
	}
	window.display();
}

void game::initMainMenuState() {
	states.push(std::make_unique<MainMenuState>(&window, &states));
}

game::game() {
	initResources();
	initWindow();
	initStates();
}

game::~game() {}

void game::run() {
	while (window.isOpen()) {
		float dt = dtClock.restart().asSeconds();

		handleEvents();
		update(dt);
		render();

		if (!states.empty() && states.top()->shouldQuit()) {
			int n = states.top()->statesToPop();
			while (n) {
				states.pop();
				--n;
			}
		}

		if (states.empty()) {
			window.close();
		}
	}
}

//void Game::pushState(std::unique_ptr<GameState> gameState) {}
//
//void Game::popState() {}
//
//void Game::changeState(std::unique_ptr<GameState> gameState) {}
