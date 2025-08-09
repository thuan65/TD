#pragma once

#include "Resource_Management.h"
#include "State.h"
#include "Sprite.h"
#include "Button.h"
#include "PlayState.h"
#include <fstream>

class LoadGameState : public State {

public:
	LoadGameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;
	void  loadGameFromFile(const string& saveFileName);

private:
	sf::Text loadGameText = sf::Text(Resource_Management::arialFont, "LOAD GAME");
	Sprite loadGameBackgroundSprite = Sprite(Resource_Management::mainMenuBackgroundTexture);//Change this later
	Sprite goBackArrowSprite = Sprite(Resource_Management::arrowTexture, { 36, 36 });
	Button saveSlot1Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40.0f }, "Save Slot 1");
	Button saveSlot2Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f }, "Save Slot 2");
	Button saveSlot3Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 40.0f }, "Save Slot 3");
	Button saveSlot4Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 80.0f }, "Save Slot 4");
	sf::Text slotEmptyText = sf::Text(Resource_Management::arialFont, "slot empty!");
	bool isEmptySaveSlot1 = true;
	bool isEmptySaveSlot2 = true;
	bool isEmptySaveSlot3 = true;
	bool isEmptySaveSlot4 = true;
	bool shouldDrawEmptySaveSlot1 = false;
	bool shouldDrawEmptySaveSlot2 = false;
	bool shouldDrawEmptySaveSlot3 = false;
	bool shouldDrawEmptySaveSlot4 = false;

	std::string saveFileName1 = "Data\\SaveGame\\GameSave1.sav";
	std::string saveFileName2 = "Data\\SaveGame\\GameSave2.sav";
	std::string saveFileName3 = "Data\\SaveGame\\GameSave3.sav";
	std::string saveFileName4 = "Data\\SaveGame\\GameSave4.sav";

	bool fileExist(const std::string& filePath);//Is the file exist
	void checkSaveSlots();//Check see if have save file
};

