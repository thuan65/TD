#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Button.h"
#include "PlayState.h"
#include "Resource_Management.h"
#include "LoadingBeforePlayState.h"
#include "Sprite.h"
#include "SoundManager.h"
#include <stack>

class MapSelectState : public State {

public:
	MapSelectState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event, sf::Vector2f mouseCoords) override;
	void update(float dt, sf::Vector2f mouseCoords) override;
	void render() override;

private:
	sf::Text mapSelectText = sf::Text(Resource_Management::font, "MAP SELECT");
	Sprite backgroundSprite = Sprite(Resource_Management::mapSelectBackgroundTexture);
	sf::RectangleShape dimOverlay = sf::RectangleShape({ (float)Resource_Management::WINDOW_WIDTH, (float)Resource_Management::WINDOW_HEIGHT });
	Sprite map1Sprite = Sprite(Resource_Management::Map_Game1[0], {Resource_Management::WINDOW_WIDTH * 0.25f + 25.0f, Resource_Management::WINDOW_HEIGHT * 0.25f + 50});
	Sprite map2Sprite = Sprite(Resource_Management::Map_Game2[0], { Resource_Management::WINDOW_WIDTH * 0.75f - 25.0f, Resource_Management::WINDOW_HEIGHT * 0.25f + 50 });
	Sprite map3Sprite = Sprite(Resource_Management::Map_Game3[0], { Resource_Management::WINDOW_WIDTH * 0.25f + 25.0f, Resource_Management::WINDOW_HEIGHT * 0.75f });
	Sprite map4Sprite = Sprite(Resource_Management::Map_Game4[0], { Resource_Management::WINDOW_WIDTH * 0.75f - 25.0f, Resource_Management::WINDOW_HEIGHT * 0.75f });
	Sprite goBackArrowSprite = Sprite(Resource_Management::leftArrowTexture, { 36, 36 });
};

