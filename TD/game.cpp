#include "game.h"

void game::initResources() {
}

void game::initWindow() {
	window = sf::RenderWindow(sf::VideoMode({ Resource_Management::WINDOW_WIDTH, Resource_Management::WINDOW_HEIGHT }), "Tower Defense");
	window.setFramerateLimit(60);
}

void game::initStates() {
	initMainMenuState();
}

void game::handleEvents(sf::Vector2f mouseCoords) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (!states.empty()) {
			states.top()->handleInput(event, mouseCoords);
		}
	}
}

void game::update(float dt, sf::Vector2f mouseCoords) {
	std::vector<State*> toRender;

	// Traverse stack from top to bottom and gather states to update
	for (auto it = states._Get_container().rbegin(); it != states._Get_container().rend(); ++it) {
		toRender.push_back(it->get());
		if (!(*it)->shouldAllowUpdateBelow()) break;
	}

	std::reverse(toRender.begin(), toRender.end());

	for (auto* state : toRender) {
		state->update(dt, mouseCoords);
	}

	SoundManager::timeAccumulator += dt;
	if (SoundManager::timeAccumulator >= SoundManager::cleanUpSoundsTime) {
		SoundManager::timeAccumulator = 0;
		SoundManager::cleanUpSounds();
	}
}

void game::render() {
	window.clear();

	std::vector<State*> toRender;

	// Traverse stack from top to bottom and gather states to render
	for (auto it = states._Get_container().rbegin(); it != states._Get_container().rend(); ++it) {
		toRender.push_back(it->get());
		if (!(*it)->shouldAllowRenderBelow()) break;
	}

	std::reverse(toRender.begin(), toRender.end());

	for (auto* state : toRender) {
		state->render();
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
		sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		handleEvents(mouseCoords);
		update(dt, mouseCoords);
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
