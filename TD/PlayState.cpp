#include "PlayState.h"

PlayState::PlayState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states, MapID mapID) :
    currentMap(mapID),
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
    GameSaver::setPlayState(this);

    pauseIconSprite.setScale({ 0.3f, 0.3f });
    speedUpIconSprite.setScale({ 0.3f, 0.3f });
    playIconSprite.setScale({ 0.3f, 0.3f });

    pressToStartText.setFillColor(sf::Color::White);
    pressToStartText.setOutlineColor(sf::Color::Black);
    pressToStartText.setOutlineThickness(1.0f);
    pressToStartText.setOrigin({ pressToStartText.getLocalBounds().position + pressToStartText.getLocalBounds().size / 2.0f });
    pressToStartText.setPosition({ 100, 24 });

    towerControl.setWaveManager(&waveControl);
    updateGUISprites();
    mapSelection.selectMap(mapID);

}

//Phuong thuc ho tro save/load
void PlayState::save(std::ostream& fileOut) {

    switch (currentMap) {
    case MapID::Map1: {
        fileOut << "Map1\n"; break;
    }
    case MapID::Map2:
    {
        fileOut << "Map2\n"; break;
    }
    case MapID::Map3:
    {
        fileOut << "Map3\n"; break;
    }
    case MapID::Map4:
    {
        fileOut << "Map4\n"; break;
    }
    }

    fileOut << lives << " " << money << " " << currentWave << " " << isGameOver << " " << playerWon << " " << isBetweenWaves << " " << timeUntilNextWave << "\n";

    waveControl.save(fileOut);
    towerControl.save(fileOut);
}

void PlayState::load(std::istream& fileIn) {
    fileIn >> lives >> money >> currentWave >> isGameOver >> playerWon >> isBetweenWaves >> timeUntilNextWave;
    waveControl.loadSave(fileIn);
    towerControl.loadSave(fileIn);
}


// --- CÁC HÀM TRỢ GIÚP ---
void PlayState::updateGUISprites() {
    livesSprites.clear();
    sf::Texture& heartTex = Resource_Management::Heart_Icon;
    const float heartScale = 0.01f; // Bạn có thể chỉnh size ở đây
    for (int i = 0; i < lives; ++i) {
        sf::Sprite heartSprite(heartTex);
        heartSprite.setScale(sf::Vector2f(heartScale, heartScale));
        float scaledHeartWidth = heartTex.getSize().x * heartScale;
        heartSprite.setPosition({ 200.f + i * (scaledHeartWidth + 5), 10.f });
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

    if (currentWave == 0) {
        currentWave++;
        waveControl.startWave(currentWave);
        return;
    }

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

void PlayState::handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) {

    if (!event.has_value()) return;

    if (pauseIconSprite.isClicked(event, mouseCoords)) {
        states->push(std::make_unique<PauseState>(window, states, &pauseIconSprite));
        SoundManager::playSound(Resource_Management::buttonClickSound);
        return;
    }

    if (speedUpIconSprite.isClicked(event, mouseCoords)) {
        if (alreadySpeedUp == false) {
            alreadySpeedUp = true;
            playSpeed *= 2;
        }
        else {
            alreadySpeedUp = false;
            playSpeed /= 2;
        }
    }

    if (playIconSprite.isClicked(event, mouseCoords)) {
        std::cout << startPlaying << " ";
        startPlaying = true;
        timeUntilNextWave = 0;
        states->push(std::make_unique<CountdownState>(window, states));
    }

    if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (keyPressed->button == sf::Mouse::Button::Left) {
            towerControl.resolveTowerAt(mouseCoords, money);
        }
    }
}

void PlayState::update(float deltaTime, sf::Vector2f mouseCoords) {
    pauseIconSprite.update(mouseCoords);
    speedUpIconSprite.update(mouseCoords);
    playIconSprite.update(mouseCoords);
    if (alreadySpeedUp == true)
        speedUpIconSprite.setColor(sf::Color(255, 255, 255, 200));
    else speedUpIconSprite.setColor(sf::Color::White);

    if (SoundManager::getMusicStatus() == sf::Music::SoundSource::Status::Paused) {
        SoundManager::resumeMusic();
    }

    if (startPlaying == true) {//Chi update khi game start
    handleWaveTiming(deltaTime);

    // Update các hệ thống
    waveControl.update(deltaTime);
    towerControl.update(deltaTime);
    bulletManager.update(deltaTime);
    gameMap.Update(deltaTime);
 
    handleEnemyResults();
    }
    updateGUISprites();
	//if (timeAccumulator >= 0.5f) {
	//	timeAccumulator -= 0.5f;
	//	currentFrame = 1 - currentFrame;
	//	backgroundSprite.setTexture(getBackgroundTexture(currentMap, currentFrame));
	//}

    // Check thắng
    if (currentWave >= WaveManager::TOTAL_WAVES && waveControl.WaveEnded()) {
        playerWon = true;
        states->push(std::make_unique<VictoryState>(window, states));
    }
    if (SoundManager::getMusicStatus() == sf::Music::SoundSource::Status::Paused) {
        SoundManager::resumeMusic();
    }
    else if (SoundManager::getMusicStatus() == sf::Music::SoundSource::Status::Stopped) {
        SoundManager::playPlayMusic();
    }
}

void PlayState::render() {
    //window->clear();
	//window->draw(backgroundSprite);

	gameMap.draw(*window);
	waveControl.draw(*window);
	towerControl.draw(*window);
	bulletManager.draw(*window);

    window->draw(speedUpIconSprite);
    if (dynamic_cast<PauseState*>(states->top().get()) == nullptr)
        window->draw(pauseIconSprite);
    if (startPlaying == false) {
        window->draw(playIconSprite);
        window->draw(pressToStartText);
    }

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

