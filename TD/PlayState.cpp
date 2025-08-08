#include "PlayState.h"

PlayState::PlayState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, MapID mapID) :
	State(window, states),
    gameMap(Resource_Management::getTexture("Map_Game1")),
    waveControl(),
    bulletManager(&waveControl),
    towerControl(window, &bulletManager),
    mapSelection(&gameMap, &bulletManager, &waveControl, &towerControl),


    // Khởi tạo các biến trạng thái
    lives(5), money(500), currentWave(0),
    isGameOver(false), playerWon(false),
    timeUntilNextWave(TIME_BETWEEN_WAVES)
	//backgroundSprite(getBackgroundTexture(mapID, currentFrame)) 
{
	pauseIconSprite.setScale({ 0.15f, 0.15f });
    towerControl.setWaveManager(&waveControl);
    updateGUISprites();
    mapSelection.selectMap(mapID);
}

// --- CÁC HÀM TRỢ GIÚP ---
void PlayState::updateGUISprites() {
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

void PlayState::drawNumber(int number, float x, float y, std::vector<sf::Sprite>& sprite_vector) {
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
void PlayState::handleWaveTiming(float deltaTime) {
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
            waveControl.startWave(currentWave);
            updateGUISprites();
        }
    }
}
void PlayState::handleEnemyResults() {
    auto result = waveControl.processRemovals();
    if (result.enemiesReachedEnd > 0) {
        lives -= result.enemiesReachedEnd;
        updateGUISprites();
        if (lives <= 0) {
            lives = 0;
            isGameOver = true;
            states->push(std::make_unique<LoseState>(window, states));
        }
    }
    if (result.moneyFromKills > 0) {
        money += result.moneyFromKills;
        updateGUISprites();
    }
}

void PlayState::handleInput(const std::optional<sf::Event>& event) {

    if (!event.has_value()) return;

    sf::Vector2f mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    //Pause Icon if mouse is on it
    if (pauseIconSprite.getGlobalBounds().contains(mouseCoords)) {
        pauseIconSprite.setPosition(pauseIconSprite.initialPosition + sf::Vector2f(0.0f, -2.0f));
    }
    else {
        pauseIconSprite.setPosition(pauseIconSprite.initialPosition);
    }

    //Handle when left click
    if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (keyPressed->button == sf::Mouse::Button::Left) {
            if (pauseIconSprite.getGlobalBounds().contains(mouseCoords)) {
                states->push(std::make_unique<PauseState>(window, states, &pauseIconSprite));
            }
            else {
                towerControl.resolveTowerAt(mouseCoords, money);
            }
        }
    }
}

void PlayState::update(float deltaTime){

    handleWaveTiming(deltaTime);

    // Update các hệ thống
	waveControl.update(deltaTime);
	towerControl.update(deltaTime);
	bulletManager.update(deltaTime);
	gameMap.Update(deltaTime);
	
    handleEnemyResults();

	/*if (timeAccumulator >= 0.5f) {
		timeAccumulator -= 0.5f;
		currentFrame = 1 - currentFrame;
		backgroundSprite.setTexture(getBackgroundTexture(currentMap, currentFrame));
	}*/

    // Check thắng
    if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
        playerWon = true;
        states->push(std::make_unique<VictoryState>(window, states));
    }
}

void PlayState::render() {
	//window->draw(backgroundSprite);
	window->clear();
	gameMap.draw(*window);
	waveControl.draw(*window);
	towerControl.draw(*window);
	bulletManager.draw(*window);

	for (const auto& sprite : livesSprites) window->draw(sprite);
	for (const auto& sprite : moneySprites) window->draw(sprite);
	for (const auto& sprite : waveSprites) window->draw(sprite);
	if (isBetweenWaves) {
		for (const auto& sprite : nextWaveTimerSprites) {
			window->draw(sprite);
		}
	}
	if (this == states->top().get()) window->draw(pauseIconSprite);
}

//const sf::Texture& PlayState::getBackgroundTexture(MapID mapID, int index) {
//	if (mapID == MapID::Map1) return Resource_Management::Map_Game1[index];
//	else if (mapID == MapID::Map2) return Resource_Management::Map_Game2[index];
//	else if (mapID == MapID::Map3) return Resource_Management::Map_Game3[index];
//	else  return Resource_Management::Map_Game4[index];
//}

