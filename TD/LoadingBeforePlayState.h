#pragma once

#include "State.h"
#include "Resource_Management.h"
#include "SoundManager.h"
#include "Sprite.h"

class LoadingBeforePlayState : public State {

public:
	LoadingBeforePlayState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	Sprite backgroundSprite = Sprite(Resource_Management::mainMenuBackgroundTexture);
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	Sprite loadingFrame = Sprite(Resource_Management::loadingFrameTexture[0], { (float)Resource_Management::WINDOW_WIDTH / 2.f, (float)Resource_Management::WINDOW_HEIGHT / 2.f });
	unsigned int currentFrame = 0;
};

